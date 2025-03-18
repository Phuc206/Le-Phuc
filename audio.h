#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL_mixer.h>

void initAudio();          // Khoi tao �m thanh
void playBackgroundMusic(); // Ph�t nhac nen
void stopBackgroundMusic(); // Dung nhac nen
void freeAudio();          // Giai ph�ng t�i nguy�n �m thanh

#endif
