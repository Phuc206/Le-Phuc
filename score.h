#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Flappy_bird.h"

class Score {
public:
    Score();
    ~Score();

    void init(SDL_Renderer* renderer);
    void update(int newScore);
    void render(SDL_Renderer* renderer, bool gameOver);
    void free();

private:
    int score;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Texture* gameOverTexture;
    SDL_Texture* finalScoreTexture;
    SDL_Rect scoreRect;
    SDL_Rect gameOverRect;
    SDL_Rect finalScoreRect;
    SDL_Color color;
    SDL_Renderer* renderer;

    void updateTexture();
    void renderGameOver(SDL_Renderer* renderer);
};

#endif
