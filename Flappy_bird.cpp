#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include "jump.h"
#include "background.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BIRD_SIZE 30
#define PIPE_WIDTH 60
#define PIPE_GAP 150
#define GRAVITY 1
#define JUMP_STRENGTH 15

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    int x, y;
    int velocity;
} Bird;

typedef struct {
    int x, height;
} Pipe;

Bird bird;
Pipe pipes[2];
int score = 0;
bool gameOver = false;

void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initJumpSound();
    initBackground(renderer);

    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 0;

    srand(time(NULL));
    pipes[0].x = SCREEN_WIDTH;
    pipes[0].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
    pipes[1].x = SCREEN_WIDTH + SCREEN_WIDTH / 2;
    pipes[1].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
}

void close() {
    freeJumpSound();
    freeBackground();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleInput(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_SPACE) {
            bird.velocity = -JUMP_STRENGTH;
            playJumpSound();
        }
    }
}

void update() {
    if (gameOver) return;

    bird.velocity += GRAVITY;
    bird.y += bird.velocity;

    if (bird.y + BIRD_SIZE > SCREEN_HEIGHT) {
        gameOver = true;
        return;
    }

    for (int i = 0; i < 2; i++) {
        pipes[i].x -= 5;

        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
            score++;
        }

        if (bird.x + BIRD_SIZE > pipes[i].x && bird.x < pipes[i].x + PIPE_WIDTH) {
            if (bird.y < pipes[i].height || bird.y + BIRD_SIZE > pipes[i].height + PIPE_GAP) {
                gameOver = true;
                return;
            }
        }
    }
}

void render() {
    renderBackground(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect birdRect = { bird.x, bird.y, BIRD_SIZE, BIRD_SIZE };
    SDL_RenderFillRect(renderer, &birdRect);

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    for (int i = 0; i < 2; i++) {
        SDL_Rect upperPipe = { pipes[i].x, 0, PIPE_WIDTH, pipes[i].height };
        SDL_Rect lowerPipe = { pipes[i].x, pipes[i].height + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (pipes[i].height + PIPE_GAP) };
        SDL_RenderFillRect(renderer, &upperPipe);
        SDL_RenderFillRect(renderer, &lowerPipe);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < score; i++) {
        SDL_Rect scoreRect = { 10 + i * 5, 10, 4, 4 };
        SDL_RenderFillRect(renderer, &scoreRect);
    }

    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect gameOverRect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 10, 100, 20 };
        SDL_RenderFillRect(renderer, &gameOverRect);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    init();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            handleInput(&event);
        }

        update();
        render();

        SDL_Delay(30);
    }

    close();
    return 0;
}
