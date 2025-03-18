#include "audio.h"
#include <iostream>

Mix_Music* backgroundMusic = NULL;  // Bien luu nhac nen

// Khoi tao �m thanh
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

// Ph�t nhac nen
void playBackgroundMusic() {
    if (backgroundMusic && !Mix_PlayingMusic()) {
        Mix_PlayMusic(backgroundMusic, -1);  // -1 de lap v� han
    }
}

// Dung nhac nen
void stopBackgroundMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

// Giai ph�ng t�i nguy�n �m thanh
void freeAudio() {
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = NULL;
    }
    Mix_CloseAudio();
}
