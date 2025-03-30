#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "Flappy_bird.h"

class Intro {
public:
    Intro();
    ~Intro();
    void init(SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer);
    void free();
    bool isStartPressed();

private:
    TTF_Font* font;
    SDL_Texture* introTexture;
    SDL_Texture* guideTexture;
    SDL_Rect introRect;
    SDL_Rect guideRect;
    SDL_Color textColor;
    bool startPressed;

    SDL_Texture* loadText(SDL_Renderer* renderer, const char* text);
};

#endif
