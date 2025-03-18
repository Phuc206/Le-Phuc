#ifndef PIPE_H
#define PIPE_H

#include <stdbool.h>
#include <SDL.h>
#include "Flappy_bird.h"

typedef struct {
    int x;       // Vi trí ngang cua ong
    int height;  // Chieu cao cua ong trên
} Pipe;

void initPipes(SDL_Renderer* renderer);
void updatePipes(bool* gameOver, int* score, int birdX, int birdY, int birdSize);
void renderPipes(SDL_Renderer* renderer);
void freePipes();

#endif
