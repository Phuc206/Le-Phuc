#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL_mixer.h>

void initAudio();
void playBackgroundMusic();
void stopBackgroundMusic();
void freeAudio();

#endif
