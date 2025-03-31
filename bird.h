#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include "Flappy_bird.h"

#define BIRD_ANIMATION_FRAMES 3

struct Bird {
    SDL_Texture* texture[BIRD_ANIMATION_FRAMES];
    int x, y;
    int velocity;
    int currentFrame;
    int frameTimer;
};

void initBird(SDL_Renderer* renderer, Bird* bird);
void renderBird(SDL_Renderer* renderer, Bird* bird);
void freeBird(Bird* bird);

#endif
