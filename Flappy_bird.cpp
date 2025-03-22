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

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Bird bird;
bool gameOver = false;
int score = 0;

// Khoi tao trò choi
void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);  // Khoi tao SDL_mixer cho MP3

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initJumpSound();
    initBackground(renderer);
    initPipes(renderer);
    initBird(renderer, &bird);  // Khoi tao chim tu bird.cpp
    initAudio();        // Khoi tao âm thanh tu audio.cpp
    playBackgroundMusic();  // Bat dau phát nhac nen
}

// Giai phóng tài nguyên
void close() {
    freeJumpSound(); // Giai phong am thanh jump
    freeBackground(); // Giai phong background
    freePipes(); // Giai phong tai nguyen ong nuoc
    freeBird();  // Giai phóng tài nguyên chim
    freeAudio();        // Giai phóng âm thanh tu audio.cpp

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();         // Thoát SDL_mixer
    SDL_Quit();
}

// Xu lý input (nhan phím)
void handleInput(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_SPACE) {
            bird.velocity = -JUMP_STRENGTH;
            playJumpSound();
        }
    }
}

// Cap nhat trang thái trò choi
void update() {
    if (gameOver) return;

    bird.velocity += GRAVITY;
    bird.y += bird.velocity;

    if (bird.y + BIRD_HEIGHT > SCREEN_HEIGHT) {  // Thay BIRD_SIZE bang BIRD_HEIGHT
        gameOver = true;
        return;
    }

    updatePipes(&gameOver, &score, bird.x, bird.y, BIRD_HEIGHT);  // Thay BIRD_SIZE bang BIRD_HEIGHT
}

// Ve hình anh lên màn hình
void render() {
    renderBackground(renderer);
    renderBird(renderer, &bird);  // Ve chim tu bird.cpp
    renderPipes(renderer);

    // Hien thi diem so
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

// Hàm chính
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
