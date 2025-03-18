#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL_mixer.h>

void initAudio();          // Khoi tao âm thanh
void playBackgroundMusic(); // Phát nhac nen
void stopBackgroundMusic(); // Dung nhac nen
void freeAudio();          // Giai phóng tài nguyên âm thanh

#endif
