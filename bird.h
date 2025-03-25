#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "Flappy_bird.h"

typedef struct {
    int x, y;
    int velocity;
} Bird;

void initBird(SDL_Renderer* renderer, Bird* bird);
void renderBird(SDL_Renderer* renderer, const Bird* bird);
void freeBird();

#endif
