#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include <stdbool.h>
#include <SDL.h>
#include "Flappy_bird.h"

#define NUM_PIPES 2

typedef struct {
    int x;
    int height;
    bool passed;
} Pipe;

void initPipes(SDL_Renderer* renderer);

void updatePipes(bool* gameOver, int* score, int birdX, int birdY, int birdHeight);

void renderPipes(SDL_Renderer* renderer);

void freePipes();

#endif
