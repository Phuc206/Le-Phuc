#include "score.h"
#include <SDL_ttf.h>
#include <sstream>

Score::Score() : score(0), font(nullptr), texture(nullptr), gameOverTexture(nullptr), finalScoreTexture(nullptr), renderer(nullptr) {}

Score::~Score() {
    free();
}

void Score::init(SDL_Renderer* renderer) {
    this->renderer = renderer;
    TTF_Init();
    font = TTF_OpenFont("04B_30__.ttf", 24);
    color = {255, 255, 255, 255};
    updateTexture();
}

void Score::update(int newScore) {
    score = newScore;
    updateTexture();
}

void Score::render(SDL_Renderer* renderer, bool gameOver) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
    }
    if (gameOver) {
        renderGameOver(renderer);
    }
}

void Score::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (gameOverTexture) {
        SDL_DestroyTexture(gameOverTexture);
        gameOverTexture = nullptr;
    }
    if (finalScoreTexture) {
        SDL_DestroyTexture(finalScoreTexture);
        finalScoreTexture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}

void Score::updateTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    std::stringstream ss;
    ss << "Score: " << score;

    SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        scoreRect = {10, 10, surface->w, surface->h};
        SDL_FreeSurface(surface);
    }
}

void Score::renderGameOver(SDL_Renderer* renderer) {
    if (!gameOverTexture) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "GAME OVER", {255, 255, 255, 255});
        if (surface) {
            gameOverTexture = SDL_CreateTextureFromSurface(renderer, surface);
            gameOverRect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - 50, surface->w, surface->h};
            SDL_FreeSurface(surface);
        }
    }

    if (!finalScoreTexture) {
        std::stringstream ss;
        ss << "Final Score: " << score;

        SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), {255, 215, 0, 255}); // Màu vàng
        if (surface) {
            finalScoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
            finalScoreRect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2, surface->w, surface->h};
            SDL_FreeSurface(surface);
        }
    }

    if (gameOverTexture) {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    }
    if (finalScoreTexture) {
        SDL_RenderCopy(renderer, finalScoreTexture, NULL, &finalScoreRect);
    }
}
