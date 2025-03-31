#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "Flappy_bird.h"

class Pause {
public:
    Pause();
    ~Pause();

    void init(SDL_Renderer* renderer);
    void handleInput(SDL_Event* event, bool& quit);
    void render(SDL_Renderer* renderer);
    bool isPaused();

private:
    bool paused;
    TTF_Font* font;
    SDL_Texture* pauseTexture;
    SDL_Texture* continueTexture;
    SDL_Texture* exitTexture;
    SDL_Rect pauseRect;
    SDL_Rect continueRect;
    SDL_Rect exitRect;
    SDL_Color textColor;

    SDL_Texture* loadText(SDL_Renderer* renderer, const char* text);
    void togglePause();
};

#endif
