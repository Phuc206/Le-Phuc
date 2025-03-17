#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SDL.h>

void initBackground(SDL_Renderer* renderer);
void renderBackground(SDL_Renderer* renderer);
void freeBackground();

#endif // BACKGROUND_H_INCLUDED
