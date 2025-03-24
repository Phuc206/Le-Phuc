#ifndef PIPE_H_INCLUDE
#define PIPE_H_INCLUDE

#include <stdbool.h>
#include <SDL.h>
#include "Flappy_bird.h"

typedef struct {
    int x,height; // Vi trí ngang cua ong va chieu cao cua ong
    bool passed; // Dung de kiem tra khi chim vuot qua ong
} Pipe;

void initPipes(SDL_Renderer* renderer);
void updatePipes(bool* gameOver, int* score, int birdX, int birdY, int birdSize);
void renderPipes(SDL_Renderer* renderer);
void freePipes();

#endif
