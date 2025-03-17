#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BIRD_SIZE 30
#define PIPE_WIDTH 60
#define PIPE_GAP 150
#define GRAVITY 1
#define JUMP_STRENGTH 15

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Mix_Chunk* jumpSound = NULL;

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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // Khoi tao SDL Video và SDL Audio
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Khoi tao SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Error: %s\n", Mix_GetError());
    }

    // Load âm thanh khi nhay
    jumpSound = Mix_LoadWAV("jump.wav");
    if (!jumpSound) {
        printf("Failed to load jump sound! Error: %s\n", Mix_GetError());
    }

    // Khoi tao chim
    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 0;

    // Khoi tao ong nuoc
    srand(time(NULL));
    pipes[0].x = SCREEN_WIDTH;
    pipes[0].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
    pipes[1].x = SCREEN_WIDTH + SCREEN_WIDTH / 2;
    pipes[1].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
}

void close() {
    Mix_FreeChunk(jumpSound); // Giai phóng bo nho âm thanh
    Mix_CloseAudio(); // Dong SDL_mixer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleInput(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_SPACE) {
            bird.velocity = -JUMP_STRENGTH; // Chim nhay len
            Mix_PlayChannel(-1, jumpSound, 0); // Choi âm thanh nhay
        }
    }
}

void update() {
    if (gameOver) return;

    // Cap nhat vi trí chim
    bird.velocity += GRAVITY;
    bird.y += bird.velocity;

    // Kiem tra va cham voi vat
    if (bird.y + BIRD_SIZE > SCREEN_HEIGHT) {
        gameOver = true;
        return;
    }

    // Cap nhat vi trí ong nuoc
    for (int i = 0; i < 2; i++) {
        pipes[i].x -= 5;

        // Neu ong nuoc di qua màn hình, tao lai ong nuoc moi
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - PIPE_GAP);
            score++;
        }

        // Kiem tra va cham voi ong nuoc
        if (bird.x + BIRD_SIZE > pipes[i].x && bird.x < pipes[i].x + PIPE_WIDTH) {
            if (bird.y < pipes[i].height || bird.y + BIRD_SIZE > pipes[i].height + PIPE_GAP) {
                gameOver = true;
                return;
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Màu nen xanh da troi
    SDL_RenderClear(renderer);

    // Ve chim
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Màu vàng
    SDL_Rect birdRect = { bird.x, bird.y, BIRD_SIZE, BIRD_SIZE };
    SDL_RenderFillRect(renderer, &birdRect);

    // Ve ong nuoc
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Màu xanh lá
    for (int i = 0; i < 2; i++) {
        SDL_Rect upperPipe = { pipes[i].x, 0, PIPE_WIDTH, pipes[i].height };
        SDL_Rect lowerPipe = { pipes[i].x, pipes[i].height + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (pipes[i].height + PIPE_GAP) };
        SDL_RenderFillRect(renderer, &upperPipe);
        SDL_RenderFillRect(renderer, &lowerPipe);
    }

    // Ve diem so (su dung hình chu nhat don gian)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trang
    for (int i = 0; i < score; i++) {
        SDL_Rect scoreRect = { 10 + i * 5, 10, 4, 4 }; // Moi diem là mot hình vuông nho
        SDL_RenderFillRect(renderer, &scoreRect);
    }

    // Ve thông báo game over (su dung hình chu nhat don gian)
    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu do
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

        SDL_Delay(30); // Toc do game
    }

    close();
    return 0;
}
