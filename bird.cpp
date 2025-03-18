#include "bird.h"
#include "Flappy_bird.h"

SDL_Texture* birdTexture = NULL;

// Khoi tao chim
void initBird(SDL_Renderer* renderer, Bird* bird) {
    SDL_Surface* surface = IMG_Load("bird.png");
    if (surface) {
        birdTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    bird->x = SCREEN_WIDTH / 4;
    bird->y = SCREEN_HEIGHT / 2;
    bird->velocity = 0;
}

// Ve chim
void renderBird(SDL_Renderer* renderer, const Bird* bird) {
    if (birdTexture) {
        SDL_Rect birdRect = { bird->x, bird->y, BIRD_WIDTH, BIRD_HEIGHT };
        SDL_RenderCopy(renderer, birdTexture, NULL, &birdRect);
    } else {
        // De phòng: ve hình vuông neu không tai duoc texture
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_Rect birdRect = { bird->x, bird->y, BIRD_WIDTH, BIRD_HEIGHT };
        SDL_RenderFillRect(renderer, &birdRect);
    }
}

// Giai phóng tài nguyên
void freeBird() {
    if (birdTexture) {
        SDL_DestroyTexture(birdTexture);
        birdTexture = NULL;
    }
}
