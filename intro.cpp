#include "intro.h"
#include <SDL_ttf.h>
#include <string>

Intro::Intro() : font(nullptr), introTexture(nullptr), guideTexture(nullptr), startPressed(false) {}

Intro::~Intro() {
    free();
}

void Intro::init(SDL_Renderer* renderer) {
    TTF_Init();
    font = TTF_OpenFont("04B_30__.ttf", 24);
    textColor = {255, 255, 255, 255};

    introTexture = loadText(renderer, "Press ENTER to Start");
    guideTexture = loadText(renderer, "SPACE to Jump, SHIFT to Pause");

    introRect = {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 40};
    guideRect = {SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 400, 30};
}

SDL_Texture* Intro::loadText(SDL_Renderer* renderer, const char* text) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Intro::show(SDL_Renderer* renderer) {
    SDL_Event event;
    bool showIntro = true;
    while (showIntro) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                showIntro = false;
                startPressed = true;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, introTexture, NULL, &introRect);
        SDL_RenderCopy(renderer, guideTexture, NULL, &guideRect);
        SDL_RenderPresent(renderer);
    }
}

void Intro::free() {
    if (introTexture) {
        SDL_DestroyTexture(introTexture);
        introTexture = nullptr;
    }
    if (guideTexture) {
        SDL_DestroyTexture(guideTexture);
        guideTexture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}

bool Intro::isStartPressed() {
    return startPressed;
}
