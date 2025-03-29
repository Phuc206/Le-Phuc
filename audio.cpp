#include "audio.h"
#include <iostream>

Mix_Music* backgroundMusic = NULL;

void initAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void playBackgroundMusic() {
    if (backgroundMusic && !Mix_PlayingMusic()) {
        if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
            std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
        }
    }
}

void stopBackgroundMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void freeAudio() {
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = NULL;
    }

    Mix_CloseAudio();
}
