#include "pause.h"
#include <SDL_ttf.h>
#include <string>

Pause::Pause() : paused(false), font(nullptr), pauseTexture(nullptr) {}

Pause::~Pause() {
    if (pauseTexture) SDL_DestroyTexture(pauseTexture);
    if (font) TTF_CloseFont(font);
}

void Pause::init(SDL_Renderer* renderer) {
    TTF_Init();
    font = TTF_OpenFont("04B_30__.ttf", 28);
    textColor = {255, 215, 0, 255}; // Mau vang
    pauseTexture = loadText(renderer, "PAUSED");
    pauseRect = {SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 20, 120, 40};
}

SDL_Texture* Pause::loadText(SDL_Renderer* renderer, const char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Pause::handleInput(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_LSHIFT || event->key.keysym.sym == SDLK_RSHIFT) {
            togglePause();
        }
    }
}

void Pause::togglePause() {
    paused = !paused;
}

void Pause::render(SDL_Renderer* renderer) {
    if (paused) {
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
    }
}

bool Pause::isPaused() {
    return paused;
}
