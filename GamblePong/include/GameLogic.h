#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "raylib.h"
#include "globals.h"

void UpdateGame(void);
void ResetGame(void);
void ResetBall(void);

// quickPlay
void ResetQUICKGame(void);
void ResetQUICKBall(void);
void DrawQuickPlay(void);
void UpdateQuickPlay(void);

void DoubleOrNothingText(void);
void DrawExplosion(int x, int y, Color color);

void InitObstacles(void);
void UpdateObstacles(void);
void DrawObstacles(void);

#endif // GAMELOGIC_H