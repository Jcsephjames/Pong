#ifndef TUTORIAL_H
#define TUTORIAL_H
#include "raylib.h"

#include "globals.h"
#include "GameLogic.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"
#include "Custom.h"
#include "Menu.h"
#include "Animations.h"

extern struct SoundManager soundManager;

extern int TutorialState;
extern void DrawTutorial(void);
extern void UpdateTutorial(void);

extern void DrawPaddle(void);
extern void ResetPaddle(void);
extern void PaddleOneMovement(void);
extern void PaddleTwoMovement(void);
extern void DrawBall(void);

#endif // TUTORIAL_H