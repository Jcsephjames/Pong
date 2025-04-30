#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "raylib.h"
#include "globals.h"

void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);
void UpdateAIPaddle(Rectangle *paddle, Vector2 ball, float speed);
void clearParticles(void);
void DrawExplosion(int x, int y, Color color);
void UpdateExplosionParticles(void);
void DoubleOrNothingText(void);
void DrawSpeedTrail(Vector2 ballPos, Vector2 ballVelocity, Color trailColor);

#endif // ANIMATIONS_H