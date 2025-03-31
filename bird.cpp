#include "bird.h"
#include <SDL_image.h>

void initBird(SDL_Renderer* renderer, Bird* bird) {
    bird->x = 100;
    bird->y = SCREEN_HEIGHT / 2;
    bird->velocity = 0;
    bird->currentFrame = 0;
    bird->frameTimer = 0;

    bird->texture[0] = IMG_LoadTexture(renderer, "bird1.png");
    bird->texture[1] = IMG_LoadTexture(renderer, "bird2.png");
    bird->texture[2] = IMG_LoadTexture(renderer, "bird3.png");
}

void renderBird(SDL_Renderer* renderer, Bird* bird) {
    bird->frameTimer++;
    if (bird->frameTimer >= 5) {
        bird->currentFrame = (bird->currentFrame + 1) % BIRD_ANIMATION_FRAMES;
        bird->frameTimer = 0;
    }

    SDL_Rect birdRect = {bird->x, bird->y, BIRD_WIDTH, BIRD_HEIGHT};
    SDL_RenderCopy(renderer, bird->texture[bird->currentFrame], NULL, &birdRect);
}

void freeBird(Bird* bird) {
    for (int i = 0; i < BIRD_ANIMATION_FRAMES; i++) {
        SDL_DestroyTexture(bird->texture[i]);
    }
}
