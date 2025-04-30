#include "raylib.h"
#include "SettingsMenu.h"
#include "globals.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"

extern struct SoundManager soundManager;
extern float player2Y, ballY, PADDLE_HEIGHT, PADDLE_SPEED;
extern bool randomStyleChosen;
extern AIPlaystyle chosenRandomStyle;
extern float player1LastHits[5];
extern int hitIndex;
extern float offset, reactionBuffer, aiSpeed;
extern bool showFPS, darkMode, musicOn, sfxOn, trailEffectOn, explosionEffectOn, backgroundEffectOn;


void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);

extern void ResetBall();
extern void DrawExplosion(int x, int y, Color color);
extern void DrawSpeedTrail(Vector2 ballPos, Vector2 ballVelocity, Color color);

void SetAIDifficulty(AIDifficulty aiDifficulty)
{
    switch (aiDifficulty)
    {
        aiSpeed = PADDLE_SPEED;
        case DIFFICULTY_EASY:
            aiSpeed = PADDLE_SPEED * 0.6f;
            reactionBuffer = 45;
            offset = GetRandomValue(-30, 30);
            break;
        case DIFFICULTY_MEDIUM:
            aiSpeed = PADDLE_SPEED * 0.8f;
            reactionBuffer = 25;
            offset = GetRandomValue(-15, 15);
            break;
        case DIFFICULTY_HARD:
            aiSpeed = PADDLE_SPEED * 0.9f;
            reactionBuffer = 5;
            offset = GetRandomValue(-5, 5);
            break;
        case DIFFICULTY_CRACKED:
            aiSpeed = PADDLE_SPEED * 1.2f;
            reactionBuffer = 0;
            offset = 0;
            break;
        default:
            break;
    }
}

// Function to handle AI playstyles
void UpdateAIPlaystyle(AIPlaystyle aiPlaystyle)
{
    switch (aiPlaystyle)
    {
        case PLAYSTYLE_RANDOM:
            if (!randomStyleChosen)
            {
                int style = GetRandomValue(1, 5); // Exclude 0 (which is RANDOM)
                chosenRandomStyle = (AIPlaystyle)style;
                randomStyleChosen = true;
            }
            UpdateAIPlaystyle(chosenRandomStyle); // Recurse safely
            break;
        case PLAYSTYLE_MIXED:
            AI_MixedPlaystyle();
            break;
        case PLAYSTYLE_DEFENSIVE:
            AI_DefensivePlaystyle();
            break;
        case PLAYSTYLE_OFFENSIVE:
            AI_OffensivePlaystyle();
            break;
        case PLAYSTYLE_TRICKY:
            AI_TrickyPlaystyle();
            break;
        case PLAYSTYLE_ADAPTIVE:
            AI_AdaptivePlaystyle();
            break;
    }
}
// Mixed playstyle AI logic
void AI_MixedPlaystyle()
{
    float aiCenter = player2Y + PADDLE_HEIGHT / 2;
    float edgeBias = 0.0f;

    int biasDirection = GetRandomValue(0, 1); // 0 = top paddle, 1 = bottom paddle
    float edgeFactor = (aiDifficulty == 0) ? 0.75f : (aiDifficulty == 1) ? 0.75f : (aiDifficulty == 2) ? 0.8f : 0.9f;
    float maxBias = (PADDLE_HEIGHT / 2.0f) * edgeFactor;

    edgeBias = (biasDirection == 0) ? -maxBias : maxBias;

    int biasChance = (aiDifficulty == 0) ? 60 : (aiDifficulty == 1) ? 70 : (aiDifficulty == 2) ? 80 : 85;
    if (GetRandomValue(0, 100) > biasChance)
        edgeBias = 0;

    float biasedCenter = aiCenter + edgeBias;
    float targetY = ballY + offset;
    if (targetY < biasedCenter - reactionBuffer && player2Y > 0)
        player2Y -= aiSpeed;
    else if (targetY > biasedCenter + reactionBuffer && player2Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
        player2Y += aiSpeed;

    // DrawCircle(SCREEN_WIDTH - 20, aiCenter + edgeBias, 5, RED); // right near paddle2
}
// Defensive playstyle AI logic
void AI_DefensivePlaystyle()
{
    float targetY = ballY + offset;
    float aiCenter = player2Y + PADDLE_HEIGHT / 2;

    if (targetY < aiCenter - reactionBuffer && player2Y > 0)
        player2Y -= aiSpeed;
    else if (targetY > aiCenter + reactionBuffer && player2Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
        player2Y += aiSpeed;

    // DrawCircle(SCREEN_WIDTH - 20, aiCenter, 5, RED);
}

// Offensive playstyle AI logic
void AI_OffensivePlaystyle()
{
    float aiCenter = player2Y + PADDLE_HEIGHT / 2;
    float edgeBias = 0.0f;

    int biasDirection = GetRandomValue(0, 1); // 0 = top paddle, 1 = bottom paddle
    float edgeFactor = (aiDifficulty == 0) ? 0.75f : (aiDifficulty == 1) ? 0.85f : (aiDifficulty == 2) ? 0.9f : 1.0f;
    float maxBias = (PADDLE_HEIGHT / 2.0f) * edgeFactor;

    edgeBias = (biasDirection == 0) ? -maxBias : maxBias;

    int biasChance = (aiDifficulty == 0) ? 100 : (aiDifficulty == 1) ? 100 : (aiDifficulty == 2) ? 100 : 100;
    if (GetRandomValue(0, 100) > biasChance)
        edgeBias = 0;

    float biasedCenter = aiCenter + edgeBias;
    float targetY = ballY + offset;
    if (targetY < biasedCenter - reactionBuffer && player2Y > 0)
        player2Y -= aiSpeed;
    else if (targetY > biasedCenter + reactionBuffer && player2Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
        player2Y += aiSpeed;

    // DrawCircle(SCREEN_WIDTH - 20, aiCenter + edgeBias, 5, RED); // right near paddle2

}
void AI_TrickyPlaystyle(void)
{
    static int trickTimer = 0;
    static int trickCooldown = 0;
    static bool trickActive = false;

    float aiCenter = player2Y + PADDLE_HEIGHT / 2;
    float targetY = ballY;

    // Occasionally activate a fake movement
    if (trickCooldown <= 0 && GetRandomValue(0, 100) < 10)
    {
        trickActive = true;
        trickTimer = GetRandomValue(15, 40); // Short misdirection
        trickCooldown = GetRandomValue(60, 120); // Cooldown before next trick
    }

    if (trickActive)
    {
        // Move in the *wrong* direction for a short time
        if (targetY < aiCenter)
            player2Y += aiSpeed; // Fake the wrong way
        else if (targetY > aiCenter)
            player2Y -= aiSpeed;

        trickTimer--;
        if (trickTimer <= 0) trickActive = false;
    }
    else
    {
        // Move normally after trick ends
        if (targetY < aiCenter - reactionBuffer)
            player2Y -= aiSpeed;
        else if (targetY > aiCenter + reactionBuffer)
            player2Y += aiSpeed;

        trickCooldown--;
    }

    // Clamp paddle
    if (player2Y < 0) player2Y = 0;
    if (player2Y > SCREEN_HEIGHT - PADDLE_HEIGHT) player2Y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}
void AI_AdaptivePlaystyle(void)
{
    float aiCenter = player2Y + PADDLE_HEIGHT / 2;

    // Average last few ball hits from player1
    float targetY = 0.0f;
    for (int i = 0; i < 5; i++) targetY += player1LastHits[i];
    targetY /= 5.0f;

    // Predictive adjustment toward player tendency
    if (targetY < aiCenter - reactionBuffer)
        player2Y -= aiSpeed;
    else if (targetY > aiCenter + reactionBuffer)
        player2Y += aiSpeed;

    // Clamp paddle
    if (player2Y < 0) player2Y = 0;
    if (player2Y > SCREEN_HEIGHT - PADDLE_HEIGHT) player2Y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}



void MainMenuPlayer1AI(void){
    float target1Y = ballY + offset;
    float aiCenter = player1Y + PADDLE_HEIGHT / 2;

    if (target1Y < aiCenter - reactionBuffer && player1Y > 0)
        player1Y -= aiSpeed;
    else if (target1Y > aiCenter + reactionBuffer && player1Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
        player1Y += aiSpeed;
}


void MainMenuAIGame(void)
{
    MainMenuPlayer1AI();
    SetAIDifficulty(aiDifficulty);
    UpdateAIPlaystyle(aiPlaystyle);

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball Collision with Walls
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZE)
        ballSpeedY = -ballSpeedY;

    // Collision with Player One Paddle
    if (ballX <= PADDLE_WIDTH && ballY + BALL_SIZE >= player1Y && ballY <= player1Y + PADDLE_HEIGHT)
    {
        ballSpeedX = -ballSpeedX;
        float hitPosition = (ballY + BALL_SIZE / 2) - (player1Y + PADDLE_HEIGHT / 2);
        ballSpeedY = hitPosition * 0.1f;
        if (explosionEffectOn)
            DrawExplosion((int)ballX, (int)ballY, playerOne);
    }

    // Collision with Player Two Paddle
    if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZE && ballY + BALL_SIZE >= player2Y && ballY <= player2Y + PADDLE_HEIGHT)
    {
        ballSpeedX = -ballSpeedX;
        float hitPosition = (ballY + BALL_SIZE / 2) - (player2Y + PADDLE_HEIGHT / 2);
        ballSpeedY = hitPosition * 0.1f;
        if (explosionEffectOn)
            DrawExplosion((int)ballX, (int)ballY, playerTwo);
    }

    // Scoring Logic
    if (ballX <= 0 || ballX >= SCREEN_WIDTH - BALL_SIZE)
    {
        ResetBall();
    }

    // Update explosion particles
    for (int i = 0; i < particleCount; i++) {
        particles[i].lifespan -= GetFrameTime(); // Decrease lifespan over time
        if (particles[i].lifespan <= 0) {
            // Remove particle by shifting remaining particles
            for (int j = i; j < particleCount - 1; j++) {
                particles[j] = particles[j + 1];
            }
            particleCount--;
            i--; // Adjust index to account for removed particle
        }
    }
}
void DrawAIGame(void)
{
    paddle1Color = playerOne;
    paddle2Color = playerTwo;

    DrawRectangle(0, (int)player1Y, PADDLE_WIDTH, PADDLE_HEIGHT, paddle1Color);
    DrawRectangle(SCREEN_WIDTH - PADDLE_WIDTH, (int)player2Y, PADDLE_WIDTH, PADDLE_HEIGHT, paddle2Color);
    DrawRectangle((int)ballX, (int)ballY, BALL_SIZE, BALL_SIZE, ballColor);
    // Draw explosion particles
    for (int i = 0; i < particleCount; i++) {
        DrawRectangle(particles[i].position.x, particles[i].position.y, 9, 9, Fade(particles[i].color, particles[i].lifespan));
    }
    if (trailEffectOn)
    {
        Vector2 ballPos = {ballX, ballY};
        Vector2 ballVelocity = {ballSpeedX, ballSpeedY};
        DrawSpeedTrail(ballPos, ballVelocity, trailColor); // Speed Trail
    }
    DrawRectangle((int)ballX, (int)ballY, BALL_SIZE, BALL_SIZE, ballColor);
}