#include "SoundManager.h"

void LoadSounds(SoundManager* sm) {
    sm->menuNavigateHorizontal = LoadSound("assets/sounds/horizontalChange.wav");
    sm->menuNavigateVertical = LoadSound("assets/sounds/verticalChange.wav");
    sm->enterMenu = LoadSound("assets/sounds/enterMenu.wav");
    sm->leaveMenu = LoadSound("assets/sounds/leaveMenu.wav");
    sm->playerOneHit = LoadSound("assets/sounds/p_1Hit.wav");
    sm->playerTwoHit = LoadSound("assets/sounds/p_2Hit.wav");
    sm->wallHit = LoadSound("assets/sounds/wallHit.wav");
    sm->scoredPoint = LoadSound("assets/sounds/scoredPoint.wav");
    sm->keyPress = LoadSound("assets/sounds/keyPress.wav");
    // sm->explosion = LoadSound("assets/sounds/explosion.wav");
    sm->backgroundMusic = LoadMusicStream("assets/sounds/menu_bgm.mp3");

    SetSoundVolume(sm->menuNavigateHorizontal, 1.0f);
    SetSoundVolume(sm->menuNavigateVertical, 1.0f);
    SetSoundVolume(sm->enterMenu, 1.0f);
    SetSoundVolume(sm->leaveMenu, 1.0f);
    SetSoundVolume(sm->playerOneHit, 1.0f);
    SetSoundVolume(sm->playerTwoHit, 1.0f);
    SetSoundVolume(sm->wallHit, 1.0f);
    SetSoundVolume(sm->scoredPoint, 1.0f);
    SetSoundVolume(sm->keyPress, 1.0f);
    // SetSoundVolume(sm->explosion, 1.0f);
    SetMusicVolume(sm->backgroundMusic, 1.0f);
}

void UnloadSounds(SoundManager* sm) {
    UnloadSound(sm->menuNavigateHorizontal);
    UnloadSound(sm->menuNavigateVertical);
    UnloadSound(sm->enterMenu);
    UnloadSound(sm->leaveMenu);
    UnloadSound(sm->playerOneHit);
    UnloadSound(sm->playerTwoHit);
    UnloadSound(sm->wallHit);
    UnloadSound(sm->scoredPoint);
    UnloadSound(sm->keyPress);
    // UnloadSound(sm->explosion);
    UnloadMusicStream(sm->backgroundMusic);
}
