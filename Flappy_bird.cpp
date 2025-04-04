#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include "Flappy_bird.h"
#include "jump.h"
#include "background.h"
#include "pipe.h"
#include "bird.h"
#include "audio.h"
#include "score.h"
#include "pause.h"
#include "intro.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Pause pause;

Bird bird;
bool gameOver = false;
int score = 0;
Score gameScore;

void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    pause.init(renderer);
    initJumpSound();
    initBackground(renderer);
    initPipes(renderer);
    initBird(renderer, &bird);
    initAudio();
    playBackgroundMusic();
    gameScore.init(renderer);
}

void close() {
    freeJumpSound();
    freeBackground();
    freePipes();
    freeBird(&bird);
    freeAudio();
    gameScore.free();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

void handleInput(SDL_Event* event, bool& quit) {
    pause.handleInput(event, quit);

    if (!pause.isPaused() && event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_SPACE) {
            bird.velocity = -JUMP_STRENGTH;
            playJumpSound();
        }
    }
}


void update() {
    if (gameOver || pause.isPaused()) return;

    bird.velocity += GRAVITY;
    bird.y += bird.velocity;

    if (bird.y + BIRD_HEIGHT > SCREEN_HEIGHT) {
        gameOver = true;
        gameScore.update(score);
        return;
    }

    updatePipes(&gameOver, &score, bird.x, bird.y, BIRD_HEIGHT);
    gameScore.update(score);
}

void render() {
    renderBackground(renderer);
    renderBird(renderer, &bird);
    renderPipes(renderer);
    gameScore.render(renderer, gameOver);
    pause.render(renderer);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    init();

    Intro intro;
    intro.init(renderer);
    intro.show(renderer);
    intro.free();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            handleInput(&event,quit);
        }

        update();
        render();

        SDL_Delay(30);
    }

    close();
    return 0;
}
