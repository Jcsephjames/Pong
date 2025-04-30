#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "raylib.h"
#include "globals.h"
#include "SoundManager.h"


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

void clearParticles(void);
void UpdateExplosionParticles(void);

void BallMovement(void);
void PaddleOneMovement(void);
void PaddleTwoMovement(void);
void AICheck(void);
void DrawPaddle(void);
void DrawBall(void);
void BallCollision(void);
void ScoringLogic(void);
void WinCondition(void);

void UpdatePortals(void);
void DrawPortals(void);
void InitPortals(void);
void UpdateGravityFlip(void);
void DrawGravityFlip(void);
void UpdateColorMadness(void);
void UpdateBallSpeedChaos(void);
void ResetScore(void);
void InitGravityFlip(void);

void InitColorMadness(void);
void RevertColors(void);
void InitBallSpeedChaos(void);
void UpdateBallSpeedChaos(void);
void InitChaosMode(void);
void UpdateChoasMde(void);
void ResetChaosModes(void);

#endif // GAMELOGIC_H