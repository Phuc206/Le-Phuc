#include "jump.h"
#include <stdio.h>

Mix_Chunk* jumpSound = NULL;

void initJumpSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Error: %s\n", Mix_GetError());
    }

    jumpSound = Mix_LoadWAV("jump.wav");
    if (!jumpSound) {
        printf("Failed to load jump sound! Error: %s\n", Mix_GetError());
    } else {
        Mix_VolumeChunk(jumpSound, 32);
    }
}

void playJumpSound() {
    if (jumpSound) {
        Mix_PlayChannel(-1, jumpSound, 0);
    }
}

void freeJumpSound() {
    Mix_FreeChunk(jumpSound);
    Mix_CloseAudio();
}
