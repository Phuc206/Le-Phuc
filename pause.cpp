#include "pause.h"
#include <SDL_ttf.h>
#include <string>

Pause::Pause() : paused(false), font(nullptr), pauseTexture(nullptr), continueTexture(nullptr), exitTexture(nullptr) {}

Pause::~Pause() {
    if (pauseTexture) SDL_DestroyTexture(pauseTexture);
    if (continueTexture) SDL_DestroyTexture(continueTexture);
    if (exitTexture) SDL_DestroyTexture(exitTexture);
    if (font) TTF_CloseFont(font);
}

void Pause::init(SDL_Renderer* renderer) {
    TTF_Init();
    font = TTF_OpenFont("04B_30__.ttf", 28);
    textColor = {255, 215, 0, 255};

    continueTexture = loadText(renderer, "SHIFT: CONTINUE");
    exitTexture = loadText(renderer, "ESC: EXIT");

    pauseRect = {SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 100, 120, 40};
    continueRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 40, 200, 40};
    exitRect = {SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 10, 120, 40};
}

SDL_Texture* Pause::loadText(SDL_Renderer* renderer, const char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Pause::handleInput(SDL_Event* event, bool& quit) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_LSHIFT || event->key.keysym.sym == SDLK_RSHIFT) {
            togglePause();
        }
        else if (event->key.keysym.sym == SDLK_ESCAPE && paused) {
            quit = true;
        }
    }
}

void Pause::togglePause() {
    paused = !paused;
}

void Pause::render(SDL_Renderer* renderer) {
    if (paused) {
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
        SDL_RenderCopy(renderer, continueTexture, NULL, &continueRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    }
}

bool Pause::isPaused() {
    return paused;
}
