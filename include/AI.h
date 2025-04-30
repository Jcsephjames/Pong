#ifndef AI_H
#define AI_H

#include "globals.h"

void SetAIDifficulty(AIDifficulty aiDifficulty);
void UpdateAIPlaystyle(AIPlaystyle aiPlaystyle);
void AI_MixedPlaystyle();
void AI_DefensivePlaystyle();
void AI_OffensivePlaystyle();
void AI_TrickyPlaystyle();
void AI_AdaptivePlaystyle();

void MainMenuPlayer1AI();
void MainMenuAIGame();
void DrawAIGame();

#endif // AI_H