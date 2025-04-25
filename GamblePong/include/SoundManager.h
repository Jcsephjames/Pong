#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "raylib.h"

typedef struct SoundManager {
    Sound menuNavigateHorizontal;
    Sound menuNavigateVertical;
    Sound enterMenu;
    Sound leaveMenu;
    Sound playerOneHit;
    Sound playerTwoHit;
    Sound wallHit;
    Sound scoredPoint;
    Sound keyPress;
    // Sound explosion;
    Music backgroundMusic;
} SoundManager;

// Function declarations for use in C
void LoadSounds(SoundManager* sm);
void UnloadSounds(SoundManager* sm);

#endif