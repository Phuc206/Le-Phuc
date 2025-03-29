#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

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
    SDL_Rect scoreRect;
    SDL_Color color;
    SDL_Renderer* renderer;

    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;

    void updateTexture();
    void renderGameOver(SDL_Renderer* renderer);
};

#endif
