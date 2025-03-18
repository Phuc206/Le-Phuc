#include "audio.h"
#include <iostream>

Mix_Music* backgroundMusic = NULL;  // Bien luu nhac nen

// Khoi tao âm thanh
void initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Tai file nhac nen
    backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (!backgroundMusic) {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

// Phát nhac nen
void playBackgroundMusic() {
    if (backgroundMusic && !Mix_PlayingMusic()) {
        Mix_PlayMusic(backgroundMusic, -1);  // -1 de lap vô han
    }
}

// Dung nhac nen
void stopBackgroundMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

// Giai phóng tài nguyên âm thanh
void freeAudio() {
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = NULL;
    }
    Mix_CloseAudio();
}
