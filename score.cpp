#include "score.h"
#include <SDL_ttf.h>
#include <sstream>
#include "Flappy_bird.h"

// Constructor: Khoi tao giá tri diem so
Score::Score() : score(0), font(nullptr), texture(nullptr), gameOverTexture(nullptr), renderer(nullptr) {}

// Destructor: Giai phóng tài nguyên
Score::~Score() {
    free();
}

// Khoi tao font chu và màu sac va hien thi diem so
void Score::init(SDL_Renderer* renderer) {
    this->renderer = renderer;
    TTF_Init();
    font = TTF_OpenFont("04B_30__.ttf", 24); // Chen font và co chu
    color = {255, 255, 255, 255}; // Màu trang
    updateTexture();
}

// Cap nhat diem so khi nguoi choi dat diem moi
void Score::update(int newScore) {
    score = newScore;
    updateTexture(); // Cap nhat lai texture cua diem so
}

// Hien thi diem so lên màn hình
void Score::render(SDL_Renderer* renderer, bool gameOver) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &scoreRect);
    }
    if (gameOver) {
        renderGameOver(renderer);
    }
}

// Giai phóng bo nho cua texture và font
void Score::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (gameOverTexture) {
        SDL_DestroyTexture(gameOverTexture);
        gameOverTexture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}

// Cap nhat texture khi diem so thay doi
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
        scoreRect = {10, 10, surface->w, surface->h}; // Vi trí hien thi trên màn hình
        SDL_FreeSurface(surface);
    }
}

// Hiển thị chữ "Game Over" khi thua
void Score::renderGameOver(SDL_Renderer* renderer) {
    if (!gameOverTexture) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", {255, 215, 0, 255}); // Màu vàng sáng
        if (surface) {
            gameOverTexture = SDL_CreateTextureFromSurface(renderer, surface);
            gameOverRect = {SCREEN_WIDTH / 2 - surface->w / 2, SCREEN_HEIGHT / 2 - surface->h / 2, surface->w, surface->h};
            SDL_FreeSurface(surface);
        }
    }
    if (gameOverTexture) {
        SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    }
}
