#include "background.h"
#include <SDL_image.h>
#include <stdio.h>

SDL_Texture* backgroundTexture = NULL;

void initBackground(SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load("background.png");
    if (!loadedSurface) {
        printf("Failed to load background image! Error: %s\n", IMG_GetError());
        return;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void renderBackground(SDL_Renderer* renderer) {
    if (backgroundTexture) {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }
}

void freeBackground() {
    SDL_DestroyTexture(backgroundTexture);
}
