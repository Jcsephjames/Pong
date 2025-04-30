
#include <raylib.h>
#include <math.h>

#include "GameLogic.h"
#include "Custom.h"
#include "globals.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"

extern struct SoundManager soundManager;
extern int gameState;

float ballX, ballY, ballSpeedX, ballSpeedY;

float player1Y, player2Y;
int lastScorer = 0;

float baseSpeed = 6.0f;
float currentSpeedMultiplier = 1.0f;


float BALL_SIZEQUICK = 12;
float BALL_SIZE = 12;

float PADDLE_HEIGHTQUICK = 100;
float PADDLE_HEIGHT = 100;

int player1Score = 0, player2Score = 0;

bool randomStyleChosen = false;

int particleCount = 0;

int numObstacles = 0;

bool ObstacleMode = true;
bool PortalMode = true;
bool GravityFlip = true;
float GravityFlipTime = 5.0f; 
bool ColorFlip = true;
float ColorFlipStartTime = 5.0f;
float ColorFlipTime = 4.0f;
bool SpeedIncrease = true;
float SpeedIncreaseStartTime = 4.0f;
float SpeedIncreaseTime = 4.0f;

float GravityFlipTimer = 0.0f;

float colorChangeTimer = 0.0f;
float colorChangeBackTimer = 0.0f;
float colorChangeInterval = 1.0f;
float chaosTimer = 0.0f;
float chaosBoostTimer = 0.0f;
float chaosSpeedIncrease = 2.0f;

bool ballIsBoosted = false;
bool boostAppliedThisCycle = false;
float originalBallSpeedX = 0.0f;
float originalBallSpeedY = 0.0f;

// Store original colors
Color BgColorStored;
Color BallColorStored;
Color playerOneStored;
Color playerTwoStored;
Color TrailColorStored;
Color ObstacleColorStored;
Color PortalColorStored;
Color ExplosionColorStored;

// Declare external functions
void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);
void DrawExplosion(int x, int y, Color color);
void DoubleOrNothingText(void);
void DrawSpeedTrail(Vector2 ballPos, Vector2 ballVelocity, Color color);

void ResetPaddle(void);
void ResetBall(void);
void clearParticles(void);

void PaddleOneMovement();
void PaddleTwoMovement();
void DrawPaddle();
void DrawBall();
void BallMovement();
void BallCollision();
void ScoringLogic();
void WinCondition();
void ResetScore();

extern Color GetRandomColor(void);
void InitColorMadness(void);
void UpdateColorMadness(void);
void InitBallSpeedChaos(void);
void UpdateBallSpeedChaos(void);
void UpdateChoasMde(void);
void InitChaosMode(void);

void ResetScore(void){
    player1Score = 0;
    player2Score = 0;
    lastScorer = 0;
    currentSpeedMultiplier = 1.0f;
    ResetBall();
    clearParticles();
}
void ResetPaddle(void){
    player1Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player2Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
}
void PaddleOneMovement(void){
    // Player One Controls
    if (IsKeyDown(KEY_W) && player1Y > 0)
        player1Y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_S) && player1Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
        player1Y += PADDLE_SPEED;
}
void PaddleTwoMovement(void){
    // Player Two Controls
    if (IsKeyDown(KEY_UP) && player2Y > 0)
            player2Y -= PADDLE_SPEED;
    if (IsKeyDown(KEY_DOWN) && player2Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
            player2Y += PADDLE_SPEED;
}
void AICheck (void){
    if (AIEnabled)
    {
    SetAIDifficulty(aiDifficulty);
    UpdateAIPlaystyle(aiPlaystyle);
    }
    else
    {
    PaddleTwoMovement();
    }
}
void BallMovement(void)
{
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Limit Ball Speed
    if (ballSpeedX > MAX_BALLSPEED)
        ballSpeedX = MAX_BALLSPEED;
    if (ballSpeedX < -MAX_BALLSPEED)
        ballSpeedX = -MAX_BALLSPEED;
    if (ballSpeedY > MAX_BALLSPEED)
        ballSpeedY = MAX_BALLSPEED;
    if (ballSpeedY < -MAX_BALLSPEED)
        ballSpeedY = -MAX_BALLSPEED;
}
void BallCollision(){
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
        player1LastHits[hitIndex] = ballY;
        hitIndex = (hitIndex + 1) % 5;
        if (sfxOn)
            PlaySound(soundManager.playerOneHit);
    }

    // Collision with Player Two Paddle
    if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZE && ballY + BALL_SIZE >= player2Y && ballY <= player2Y + PADDLE_HEIGHT)
    {
        ballSpeedX = -ballSpeedX;
        float hitPosition = (ballY + BALL_SIZE / 2) - (player2Y + PADDLE_HEIGHT / 2);
        ballSpeedY = hitPosition * 0.1f;
        if (explosionEffectOn)
            DrawExplosion((int)ballX, (int)ballY, playerTwo);
        if (sfxOn)
            PlaySound(soundManager.playerTwoHit);
    }
}
void ScoringLogic (void)
{
    // Ball Out of Bounds
    if (ballX < 0)
    {
        player2Score++;
        lastScorer = 2;
        currentSpeedMultiplier *= (gameState == 4) ? 1.30f : speedIncrement;
        ResetBall();
        if (sfxOn)
            PlaySound(soundManager.scoredPoint);
    }
    else if (ballX > SCREEN_WIDTH)
    {
        player1Score++;
        lastScorer = 1;
        currentSpeedMultiplier *= (gameState == 4) ? 1.30f : speedIncrement;
        ResetBall();
        if (sfxOn)
            PlaySound(soundManager.scoredPoint);
    }
}
void WinCondition(void)
{
    // Check Win Condition
    if (gameState == 1 && (player1Score >= 10 || player2Score >= 10)) // Standard Game Mode
        gameState = (player1Score >= 10) ? 2 : 3;
    else if (gameState == 4 && (player1Score >= 20 || player2Score >= 20)) // Double or Nothing Mode
        gameState = (player1Score >= 20) ? 2 : 3;;
}
// Reset Game State
void ResetGame(void)
{
    player1Score = 0;
    player2Score = 0;
    ResetPaddle();
    currentSpeedMultiplier = 1.0f;
    ResetBall();
    clearParticles();
    randomStyleChosen = false;

    gameState = 1;
}
// Reset Ball Position and Speed
void ResetBall(void)
{
    ballX = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    ballY = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

    // RESET PADDLE AFTER EVERY CONCEDED POINT
    ResetPaddle();

    ballSpeedX = (lastScorer == 1) ? baseSpeed : -baseSpeed;
    ballSpeedY = 0;

    ballSpeedX *= currentSpeedMultiplier;

}
void UpdateGame(void)
{
    PaddleOneMovement();
    AICheck();
    BallMovement();
    BallCollision();
    ScoringLogic();
    WinCondition();
    UpdateExplosionParticles();
}
// Render/Draw Game Screen
// Draw Paddle
void DrawPaddle(void)
{
    DrawRectangle(0, (int)player1Y, PADDLE_WIDTH, PADDLE_HEIGHT, paddle1Color);
    DrawRectangle(SCREEN_WIDTH - PADDLE_WIDTH, (int)player2Y, PADDLE_WIDTH, PADDLE_HEIGHT, paddle2Color);
}
void DrawBall(void)
{
    switch (BallType)
    {
    case 0:
        DrawRectangle((int)ballX, (int)ballY, BALL_SIZE, BALL_SIZE, ballColor);
        break;
    case 1:
        DrawCircle((int)ballX, (int)ballY, BALL_SIZE / 2, ballColor);
        break;
    }

}
void DrawGameScreen(void)
{
    paddle1Color = playerOne;
    paddle2Color = playerTwo;

    BeginDrawing();
    ClearBackground(bgColor);

    DrawPaddle();
    DrawBall();

    DrawText(TextFormat("Player 1: %d", player1Score), SCREEN_WIDTH / 4 - 60, 20, 30, playerOne);
    DrawText(TextFormat("Player 2: %d", player2Score), SCREEN_WIDTH * 3 / 4 - 60, 20, 30, playerTwo);

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

    if (gameState == 4) // Double or Nothing
    {
        DoubleOrNothingText(); // Bounce Text
    }
    
    if (paused)
    {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 50) / 2, SCREEN_HEIGHT / 2 - 25, 50, RED);
        DrawText("Press M for Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M for Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, textColor);
    }
    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}
//                                                                            -- QUICK PLAY --
void ResetQUICKGame(void)
{
    player1Score = 0;
    player2Score = 0;
    ResetPaddle();
    currentSpeedMultiplier = 1.0f;
    ResetQUICKBall();
    clearParticles();
    randomStyleChosen = false;
    gameState = 11;
}
// Reset Ball Position and Speed for QUCICK PLAY
void ResetQUICKBall(void)
{
    ballX = SCREEN_WIDTH / 2 - BALL_SIZEQUICK / 2;
    ballY = SCREEN_HEIGHT / 2 - BALL_SIZEQUICK / 2;

    ballSpeedX = (lastScorer == 1) ? baseSpeedQUICK : -baseSpeedQUICK;
    ballSpeedY = 0;

    ballSpeedX *= currentSpeedMultiplier;
}

// DRAW QUICK PLAY
void DrawQuickPlay(void)
{
    paddle1Color = playerOne;
    paddle2Color = playerTwo;

    BeginDrawing();
    ClearBackground(bgColor);

    DrawBall();
    DrawPaddle();

    DrawText(TextFormat("Player 1: %d", player1Score), SCREEN_WIDTH / 4 - 60, 20, 30, playerOne);
    DrawText(TextFormat("Player 2: %d", player2Score), SCREEN_WIDTH * 3 / 4 - 60, 20, 30, playerTwo);

    // Draw explosion particles
    for (int i = 0; i < particleCount; i++) {
        DrawRectangle(particles[i].position.x, particles[i].position.y, 9, 9, Fade(particles[i].color, particles[i].lifespan));
    }
    // Trail Effect
    if (trailEffectOn)
    {
        Vector2 ballPos = {ballX, ballY};
        Vector2 ballVelocity = {ballSpeedX, ballSpeedY};
        DrawSpeedTrail(ballPos, ballVelocity, trailColor); // Speed Trail
    }

    if (gameState == 4) // Double or Nothing NOT IN QUICK PLAY AT THE MOMENT
    {
        DoubleOrNothingText(); // Bounce Text
    }

    DrawRectangle((int)ballX, (int)ballY, BALL_SIZEQUICK, BALL_SIZEQUICK, ballColor);

    if (paused)
    {
        DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 50) / 2, SCREEN_HEIGHT / 2 - 25, 50, RED);
        DrawText("Press M for Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M for Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, textColor);
    }
    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}

// Update Quick Play Logic (SIMILAR TO THE SETUP MODE)
void UpdateQuickPlay(void)
{
    // Player Controls
    if (IsKeyDown(KEY_W) && player1Y > 0)
        player1Y -= 3;
    if (IsKeyDown(KEY_S) && player1Y < SCREEN_HEIGHT - PADDLE_HEIGHTQUICK)
        player1Y += 3;
        // AI / Player Two Controls
    if (AIEnabled)
    {
    SetAIDifficulty(aiDifficulty);
    UpdateAIPlaystyle(aiPlaystyle);
    }
    else
    {
        // Player Two Controled Controls
        if (IsKeyDown(KEY_UP) && player2Y > 0)
            player2Y -= PADDLE_SPEED;
        if (IsKeyDown(KEY_DOWN) && player2Y < SCREEN_HEIGHT - PADDLE_HEIGHT)
            player2Y += PADDLE_SPEED;
    }

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball Collision with Walls
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZEQUICK){
        ballSpeedY = -ballSpeedY;
        if (sfxOn)
            PlaySound(soundManager.wallHit);
    }
    // Collision with Player One Paddle
    if (ballX <= PADDLE_WIDTH && ballY + BALL_SIZEQUICK >= player1Y && ballY <= player1Y + PADDLE_HEIGHTQUICK)
    {
        ballSpeedX = -ballSpeedX;
        float hitPosition = (ballY + BALL_SIZEQUICK / 2) - (player1Y + PADDLE_HEIGHTQUICK / 2);
        ballSpeedY = hitPosition * 0.1f;
        if (explosionEffectOn)
            DrawExplosion((int)ballX, (int)ballY, playerOne);
        player1LastHits[hitIndex] = ballY;
        hitIndex = (hitIndex + 1) % 5;
        if (sfxOn)
            PlaySound(soundManager.playerOneHit);
    }

    // Collision with Player Two Paddle
    if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZEQUICK && ballY + BALL_SIZEQUICK >= player2Y && ballY <= player2Y + PADDLE_HEIGHTQUICK)
    {
        ballSpeedX = -ballSpeedX;
        float hitPosition = (ballY + BALL_SIZEQUICK / 2) - (player2Y + PADDLE_HEIGHTQUICK / 2);
        ballSpeedY = hitPosition * 0.1f;
        if (explosionEffectOn)
            DrawExplosion((int)ballX, (int)ballY, playerTwo);
        if (sfxOn)
            PlaySound(soundManager.playerTwoHit);
    }
    // Max Ball Speed
    if (ballSpeedX > MAX_BALLSPEED)
        ballSpeedX = MAX_BALLSPEED;
    if (ballSpeedX < -MAX_BALLSPEED)
        ballSpeedX = -MAX_BALLSPEED;
    if (ballSpeedY > MAX_BALLSPEED)
        ballSpeedY = MAX_BALLSPEED;
    if (ballSpeedY < -MAX_BALLSPEED)
        ballSpeedY = -MAX_BALLSPEED;
    // Scoring Logic
    if (ballX <= 0 || ballX >= SCREEN_WIDTH - BALL_SIZEQUICK)
    {
        if (ballX <= 0) // Player Two
        {
            PlaySound(soundManager.scoredPoint);
            player2Score++;
            lastScorer = 2;
        }
        else // Player One
        {
            PlaySound(soundManager.scoredPoint);
            player1Score++;
            lastScorer = 1;
        }

        currentSpeedMultiplier *= (gameState == 4) ? 1.30f : speedIncrementQUICK;
        ResetBall();
    }

    // Check Win Condition
    if (gameState == 11 && (player1Score >= 10 || player2Score >= 10)) // Standard Game Mode
        gameState = (player1Score >= 10) ? 2 : 3;
    else if (gameState == 4 && (player1Score >= 20 || player2Score >= 20)) // Double or Nothing Mode
        gameState = (player1Score >= 20) ? 2 : 3;;
    
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
//                                                                              -- OBSTACLE MODE --
void InitObstacles(void) {
    numObstacles = GetRandomValue(1, OBSTACLEamount);
    int movingIndex = GetRandomValue(0, numObstacles - 1); // One moving obstacle

    for (int i = 0; i < numObstacles; i++) {
        obstacles[i].position.x = GetRandomValue(SCREEN_WIDTH / 4, SCREEN_WIDTH * 3 / 4);
        obstacles[i].position.y = GetRandomValue(SCREEN_HEIGHT / 4, SCREEN_HEIGHT * 3 / 4);

        obstacles[i].size.x = PADDLE_WIDTH + 10;
        obstacles[i].size.y = PADDLE_HEIGHT + 20;
        obstacles[i].active = true;

        // Mark one obstacle as moving
        obstacles[i].isMoving = (i == movingIndex);

        if (obstacles[i].isMoving) {
            float range = GetRandomValue(60, 250);
            obstacles[i].startY = obstacles[i].position.y;
            obstacles[i].endY = obstacles[i].startY + range;

            if (obstacles[i].endY + obstacles[i].size.y > SCREEN_HEIGHT) {
                obstacles[i].endY = SCREEN_HEIGHT - obstacles[i].size.y;
            }

            obstacles[i].movingDown = true;
        }
    }
}
void UpdateObstacles(void) {
    for (int i = 0; i < numObstacles; i++) {
        Rectangle obs = { obstacles[i].position.x, obstacles[i].position.y, obstacles[i].size.x, obstacles[i].size.y };
        Rectangle ball = { ballX, ballY, BALL_SIZE, BALL_SIZE };
        if (obstacles[i].isMoving) {
            if (obstacles[i].movingDown) {
                obstacles[i].position.y += 5.0f;
                if (obstacles[i].position.y >= obstacles[i].endY)
                    obstacles[i].movingDown = false;
            } else {
                obstacles[i].position.y -= 5.0f;
                if (obstacles[i].position.y <= obstacles[i].startY)
                    obstacles[i].movingDown = true;
            }
        }
        if (CheckCollisionRecs(obs, ball)) {
            // Determine which side of the obstacle the ball hit
            float overlapLeft = (ballX + BALL_SIZE) - obstacles[i].position.x;
            float overlapRight = (obstacles[i].position.x + obstacles[i].size.x) - ballX;
            float overlapTop = (ballY + BALL_SIZE) - obstacles[i].position.y;
            float overlapBottom = (obstacles[i].position.y + obstacles[i].size.y) - ballY;

            float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
            float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

            if (minOverlapX < minOverlapY) {
                ballSpeedX = -ballSpeedX;
                // Push ball outside on X-axis
                if (overlapLeft < overlapRight)
                    ballX = obstacles[i].position.x - BALL_SIZE;
                else
                    ballX = obstacles[i].position.x + obstacles[i].size.x;
            } else {
                ballSpeedY = -ballSpeedY;
                // Push ball outside on Y-axis
                if (overlapTop < overlapBottom)
                    ballY = obstacles[i].position.y - BALL_SIZE;
                else
                    ballY = obstacles[i].position.y + obstacles[i].size.y;
            }
        }
    }
}
void DrawObstacles(void) {
    for (int i = 0; i < numObstacles; i++) {
        DrawRectangle(obstacles[i].position.x, obstacles[i].position.y,
                      obstacles[i].size.x, obstacles[i].size.y, obstacleColor);
    }
}
//                                                                                       - CHAOS MODE -
void ResetChaosModes(void) {
    numObstacles = 0;
    portalAmount = 0;

    RevertColors();

    if (ballIsBoosted) {
        ballSpeedX = originalBallSpeedX;
        ballSpeedY = originalBallSpeedY;
    }

    ballIsBoosted = false;
    boostAppliedThisCycle = false;

    GravityFlipTimer = 0.0f;
    colorChangeTimer = 0.0f;
    colorChangeBackTimer = 0.0f;
    chaosTimer = 0.0f;
    chaosBoostTimer = 0.0f;
    portalCooldown = 0.0f;
}
void UpdateChoasMde(void) {
    if (PortalMode) {
        UpdatePortals();
        DrawPortals();
    }
    if (ObstacleMode) {
        UpdateObstacles();
        DrawObstacles();
    }
    if (GravityFlip) {
        UpdateGravityFlip();
        DrawGravityFlip();
    }
    if (ColorFlip) {
        UpdateColorMadness();
    }
    if (SpeedIncrease) {
        UpdateBallSpeedChaos();
    }
}
void InitChaosMode(){
    if (PortalMode) {
        InitPortals();
    }
    if (ObstacleMode) {
        InitObstacles();
    }
    if (GravityFlip) {
        InitGravityFlip();
    }
    if (ColorFlip) {
        InitColorMadness();
    }
    if (SpeedIncrease) {
        InitBallSpeedChaos();
    }
}
void InitPortals() {
    portalAmount = GetRandomValue(1, numPortals); // Random number of portals

    for (int i = 0; i < portalAmount; i++) {
        // Set the entrance (position1) and exit (position2) of each portal
        portals[i].size = (Vector2){8, 23}; // or whatever size looks good

        portals[i].position1.x = GetRandomValue(SCREEN_WIDTH / 4, SCREEN_WIDTH * 3 / 4);
        portals[i].position1.y = GetRandomValue(SCREEN_HEIGHT / 4, SCREEN_HEIGHT * 3 / 4);

        portals[i].position2.x = GetRandomValue(SCREEN_WIDTH / 4, SCREEN_WIDTH * 3 / 4);
        portals[i].position2.y = GetRandomValue(SCREEN_HEIGHT / 4, SCREEN_HEIGHT * 3 / 4);

        portals[i].color = portalColor;

        portals[i].isActive = true; // Set the portal to be active
    }
}
float dist(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
void UpdatePortals(void) {
    if (portalCooldown > 0.0f) {
        portalCooldown -= GetFrameTime();
        return;
    }
    for (int i = 0; i < numPortals; i++) {
        if (!portals[i].isActive) continue;

        Vector2 ballPos = (Vector2){ballX, ballY};
        float radius = ((portals[i].size.x) * 0.4f) + portals[i].size.y;

        if (dist(ballPos, portals[i].position1) <= radius) {
            ballSpeedY = GetRandomValue(0, 1) == 0 ? -ballSpeedY : ballSpeedY;

            ballX = portals[i].position2.x;
            ballY = portals[i].position2.y;
            portalCooldown = 1.0f;
            break;
        }

        if (dist(ballPos, portals[i].position2) <= radius) {
            ballSpeedY = GetRandomValue(0, 1) == 0 ? -ballSpeedY : ballSpeedY;

            ballX = portals[i].position1.x;
            ballY = portals[i].position1.y;
            portalCooldown = 1.0f;
            break;
        }
    }
}
void DrawPortals(void) {
    for (int i = 0; i < numPortals; i++) {
        if (!portals[i].isActive) continue;
        portals[i].color = portalColor;
        DrawEllipse(portals[i].position1.x, portals[i].position1.y, portals[i].size.x, portals[i].size.y, portals[i].color);
        DrawEllipse(portals[i].position2.x, portals[i].position2.y, portals[i].size.x, portals[i].size.y, portals[i].color);
    }
}
void InitGravityFlip(void) {
    float GravityFlipTimer = 0.0f;
}
void UpdateGravityFlip(void) {
    GravityFlipTimer += GetFrameTime();
    if (GravityFlipTimer > GravityFlipTime) {
        if (GetRandomValue(0, 100) < 25) {
            // Flip gravity
            ballSpeedY = -ballSpeedY;
            ballSpeedX = -ballSpeedX;
        }
        GravityFlipTimer = 0.0f;
    }
}
void DrawGravityFlip(void) {

    // Draw a visual effect for gravity flip
}
void InitColorMadness(void) {
    // Store original colors
    BgColorStored = bgColor;
    BallColorStored = ballColor;
    playerOneStored = playerOne;
    playerTwoStored = playerTwo;
    TrailColorStored = trailColor;
    ObstacleColorStored = obstacleColor;
    PortalColorStored = portalColor;
    ExplosionColorStored = explosionColor;

    // Set a timer for color changes
    float colorChangeTimer = 0.0f;
    float colorChangeBackTimer = 0.0f;
    // Initialize color madness effect Start by storing the original colors when entering game
}
void UpdateColorMadness(void) { // Timer and randomiser decides if colors should be changed
//   Randomly change colors of ball, paddles, and background then start timer that changes them back again
    colorChangeTimer += GetFrameTime();
    if (colorChangeTimer > ColorFlipStartTime) {
        if (GetRandomValue(0, 100) < 50) {
        bgColor        = GetRandomColor();
        ballColor      = GetRandomColor();
        playerOne      = GetRandomColor();
        playerTwo      = GetRandomColor();
        trailColor     = GetRandomColor();
        obstacleColor  = GetRandomColor();
        portalColor    = GetRandomColor();
        explosionColor = GetRandomColor();
        colorChangeBackTimer += GetFrameTime();
        }
    }
    // Randomly change colors of ball, paddles, background, obstacles, and portals
    // Use a timer to revert back to original colors
    if (colorChangeBackTimer > ColorFlipTime) {
        RevertColors();

        colorChangeBackTimer = 0.0f; // Reset the timer to reset the timer
        colorChangeTimer = 0.0f; // Reset the timer
    }
}
void RevertColors (void){
    bgColor        = BgColorStored;
    ballColor      = BallColorStored;
    playerOne      = playerOneStored;
    playerTwo      = playerTwoStored;
    trailColor     = TrailColorStored;
    obstacleColor  = ObstacleColorStored;
    portalColor    = PortalColorStored;
    explosionColor = ExplosionColorStored;
}
void InitBallSpeedChaos(void) {
    chaosTimer = 0.0f;
    chaosBoostTimer = 0.0f;
    ballIsBoosted = false;
    boostAppliedThisCycle = false;
}
void UpdateBallSpeedChaos(void) {
    chaosTimer += GetFrameTime();

    // Wait 5 seconds
    if (!ballIsBoosted && !boostAppliedThisCycle && chaosTimer > SpeedIncreaseStartTime) {
        if (GetRandomValue(0, 100) < 50) {
            originalBallSpeedX = ballSpeedX;
            originalBallSpeedY = ballSpeedY;
            ballSpeedX *= chaosSpeedIncrease;
            ballSpeedY *= chaosSpeedIncrease;
            ballIsBoosted = true;
            boostAppliedThisCycle = true;
            chaosBoostTimer = 0.0f;
        } else {
            // Skip boost this cycle
            chaosTimer = 0.0f;
            boostAppliedThisCycle = false;
        }
    }

    // If boosted, count 3 seconds then revert
    if (ballIsBoosted) {
        chaosBoostTimer += GetFrameTime();
        if (chaosBoostTimer > SpeedIncreaseTime) {
            ballSpeedX = originalBallSpeedX;
            ballSpeedY = originalBallSpeedY;
            ballIsBoosted = false;
            boostAppliedThisCycle = false;
            chaosTimer = 0.0f;
        }
    }
}
