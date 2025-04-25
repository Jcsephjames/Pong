#include "raylib.h"
#include <math.h>

#include "globals.h"
#include "GameLogic.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"
#include "Custom.h"
#include "Menu.h"
#include "Animations.h"


//                                                                      -- Animations --  


//                                                                         - Bounce Animations -

void UpdateSelectionHighlight(SelectionHighlight *highlight)
{
    if (!highlight->animating) return;

    highlight->frames++;

    if (highlight->frames <= highlight->maxFrames / 2)
        highlight->offset = highlight->dashDistance * ((float)highlight->frames / (highlight->maxFrames / 2));
    else
        highlight->offset = highlight->dashDistance * (1.0f - ((float)(highlight->frames - highlight->maxFrames / 2) / (highlight->maxFrames / 2)));

    if (highlight->frames >= highlight->maxFrames) {
        highlight->animating = false;
        highlight->offset = 0;
    }
}
void StartSelectionBounce(SelectionHighlight *highlight) {
    highlight->animating = true;
    highlight->frames = 0;
}


//                                                                          - Title Screen Animations -
void UpdateAIPaddle(Rectangle *paddle, Vector2 ball, float speed) {
    if (ball.y > paddle->y + paddle->height / 2) paddle->y += speed;
    else if (ball.y < paddle->y + paddle->height / 2) paddle->y -= speed;
}
//                                                                                 -- PADDLE EXPLOSION -- 
void clearParticles(void){
    particleCount = 0;
}
void DrawExplosion(int x, int y, Color color) {
    if (explosionEffectOn) {
        for (int i = 0; i < explosionPower * 20; i++) {
            if (particleCount < MAX_PARTICLES) {
                particles[particleCount].position = (Vector2){x + GetRandomValue(-15, 15), y + GetRandomValue(-15, 15)};
                particles[particleCount].color = color;
                particles[particleCount].lifespan = 0.8f;
                particleCount++;
            }
        }
    }
}

//                                                                          - Double or nothing -
// - Bounce Text -
void DoubleOrNothingText(void)
{
    static float bounce = 0;
    bounce += 0.15f; // Speed of bounce
    float offset = sin(bounce) * 30; // Range of bounce

    DrawText("DOUBLE OR NOTHING", SCREEN_WIDTH / 2 - MeasureText("DOUBLE OR NOTHING", 50) / 2,
             SCREEN_HEIGHT / 2 + (int)offset, 50, GOLD);
}
// - FIRE TRAIL -
void DrawSpeedTrail(Vector2 ballPos, Vector2 ballVelocity, Color trailColor) {
    int numTrailParticles = 10; // No. of squares in trail
    float stepSize = 1.0f; // Tightness of trail squares
    float squareSize = BALL_SIZE; // Size of squares

    for (int i = 0; i < numTrailParticles; i++) {
        Vector2 trailPos = {
            ballPos.x - (ballVelocity.x * i * stepSize),
            ballPos.y - (ballVelocity.y * i * stepSize)
        };

        DrawRectangle(trailPos.x - squareSize / 2, trailPos.y - squareSize / 2, squareSize, squareSize, trailColor);
    }
}