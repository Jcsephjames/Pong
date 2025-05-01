#include "raylib.h"
#include <math.h>

#include "globals.h"
#include "GameLogic.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"
#include "Custom.h"
#include "Menu.h"


extern struct SoundManager soundManager;

// Declare external functions
void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);

void UpdateAIPaddle(Rectangle *paddle, Vector2 ball, float speed);
void ResetQUICKGame();
void InitObstacles();

void ResetMenu(void)
{
    menuSelection = 0;
    settingsSelection = 0;
    setUpSeclection = 0;
    selectorSelection = 0;
    TutorialState = 0;
    customizationSelection = 0;
}
//                                                           -- TITLE SCREEN --
void DrawTitleScreen(void)
{
    BeginDrawing();
    ClearBackground(bgColor);
    DrawText("Gamble Pong", SCREEN_WIDTH / 2 - MeasureText("Gamble Pong", 50) / 2, 100, 50, textColor);
    DrawText("Gamble Safe", 10, 10, 20, darkMode ? LIGHTGRAY : DARKGRAY);
    DrawText(TextFormat("Press H to turn AI %s", AIEnabled ? "OFF" : "ON"), SCREEN_WIDTH - MeasureText("Press H to turn AI OFF", 20) - 10, 10, 20, textColor);
    DrawText("Press t for Tutorial", SCREEN_WIDTH / 2 - MeasureText("Press t for Tutorial", 20) / 2, 160, 20, textColor);

    Color playColor = (menuSelection == 0) ? textColor : GRAY;
    Color modesColor = (menuSelection == 1) ? textColor : GRAY;
    Color customizationColor = (menuSelection == 2) ? textColor : GRAY;
    Color settingsColor = (menuSelection == 3) ? textColor : GRAY;
    Color CreditsColor = (menuSelection == 4) ? textColor : GRAY;

    DrawText("QUICK PLAY", SCREEN_WIDTH / 2 - MeasureText("QUICK PLAY", 35) / 2 + ((menuSelection == 0) ? selectionBounceMenu.offset : 0), 250, 35, playColor);
    DrawText("MODES", SCREEN_WIDTH / 2 - MeasureText("MODES", 35) / 2 + ((menuSelection == 1) ? selectionBounceMenu.offset : 0), 300, 35, modesColor);
    DrawText("CUSTOMIZATION", SCREEN_WIDTH / 2 - MeasureText("CUSTOMIZATION", 35) / 2 + ((menuSelection == 2) ? selectionBounceMenu.offset : 0), 350, 35, customizationColor);
    DrawText("SETTINGS", SCREEN_WIDTH / 2 - MeasureText("SETTINGS", 35) / 2 + ((menuSelection == 3) ? selectionBounceMenu.offset : 0), 400, 35, settingsColor);
    DrawText("CREDITS", SCREEN_WIDTH / 2 - MeasureText("CREDITS", 35) / 2 + ((menuSelection == 4) ? selectionBounceMenu.offset : 0), 450, 35, CreditsColor);


    DrawText("Press C to view controls", 10, SCREEN_HEIGHT - 30, 20, textColor);

    if (showFPS) {
        DrawFPS(10, 30);
    }
    EndDrawing();
}

void UpdateTitleScreen()
{
    Vector2 bgBallPos = {0};
    Vector2 bgBallSpeed = {5.0f, 3.0f};
    Rectangle aiPaddleLeft = {0};
    Rectangle aiPaddleRight = {0};

    UpdateAIPaddle(&aiPaddleLeft, bgBallPos, 2.0f);
    UpdateAIPaddle(&aiPaddleRight, bgBallPos, 2.0f);

    bgBallPos.x += bgBallSpeed.x;
    bgBallPos.y += bgBallSpeed.y;

    // Ball collision with screen edges
    if (bgBallPos.y <= 0 || bgBallPos.y >= GetScreenHeight()) {
        bgBallSpeed.y *= -1;
    }
    // Simple paddle collision
    if (CheckCollisionCircleRec(bgBallPos, 5, aiPaddleLeft) || CheckCollisionCircleRec(bgBallPos, 5, aiPaddleRight)) {
        bgBallSpeed.x *= -1;
    }

    UpdateSelectionHighlight(&selectionBounceMenu);
    const int titleOptions = 5;
    // Navigation
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        menuSelection = (menuSelection + 1) % titleOptions;
        StartSelectionBounce(&selectionBounceMenu);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        menuSelection = (menuSelection - 1 + titleOptions) % titleOptions;
        StartSelectionBounce(&selectionBounceMenu);
        PlaySound(soundManager.menuNavigateVertical);
    }
    // Selection process
    if (IsKeyPressed(KEY_ENTER))
    {
        if (sfxOn)
            PlaySound(soundManager.enterMenu);
        if (menuSelection == 0) {
            if (!AIEnabled) {
                ResetScore();
                ResetQUICKGame();
                gameState = 11; // QUICK PLAY
            } else {
                ResetScore();
                ResetQUICKGame();
                ResetMenu();
                gameState = 14; // QUICK PLAY SELECTOR
            }
        }
        else if (menuSelection == 1){
            ResetMenu();
            gameState = 7; // Modes Menu
            }
        else if (menuSelection == 2){
            ResetMenu();
            gameState = 12; // Customization Menu
            }
        else if (menuSelection == 3){
            ResetMenu();
            gameState = 5; // Settings Menu
        }
        else if (menuSelection == 4){
            ResetMenu();
            gameState = 13; // Credits
        }
    }
    if (IsKeyPressed(KEY_C)){ // Controls Screen
        if (sfxOn)
            PlaySound(soundManager.keyPress);
        gameState = 6;
    }
    if (IsKeyPressed(KEY_V)){ // Settings Screen
        if (sfxOn)
            PlaySound(soundManager.keyPress);
        gameState = 5;
    }
    if (IsKeyPressed(KEY_H)){// Toggle AI
        if (sfxOn)
            PlaySound(soundManager.keyPress);
        AIEnabled = !AIEnabled;
    }
    if (IsKeyPressed(KEY_T)){ // Tutorial
        if (sfxOn)
            PlaySound(soundManager.keyPress);
        ResetPaddle();
        TutorialState = 0;
        AIEnabled = true;
        aiDifficulty = DIFFICULTY_EASY;
        gameState = 15;

    }
}
// Post Game Menu
void DrawPostGameMenu(const char *winnerText)
{

    BeginDrawing();
    ClearBackground(bgColor);

    DrawText(winnerText, SCREEN_WIDTH / 2 - MeasureText(winnerText, 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, textColor);
    DrawText("Press R to Restart", SCREEN_WIDTH / 2 - MeasureText("Press R to Restart", 20) / 2, SCREEN_HEIGHT / 2 + 50, 20, textColor);
    DrawText("Press D for Double or Nothing", SCREEN_WIDTH / 2 - MeasureText("Press D for Double or Nothing", 20) / 2, SCREEN_HEIGHT / 2 + 90, 20, textColor);
    DrawText("Press M for Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M for Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 130, 20, textColor);
    EndDrawing();
}
void HandlePostGameOptions(void)
{
    if (IsKeyDown(KEY_R)) // Restart Game
        ResetGame();
    else if (IsKeyDown(KEY_D)) // Double or Nothing Mode
    {
        currentSpeedMultiplier = 1.0f;
        gameState = 4; 
        trailEffectOn = true;
        ResetBall();
    }
    else if (IsKeyDown(KEY_M)) // Main Menu
    {
        if (sfxOn)
            PlaySound(soundManager.leaveMenu);
        gameState = 0;
    }
}

//                                                                                       -- Controls Screen --
void DrawControlsScreen(void)
{
    BeginDrawing();
    ClearBackground(bgColor);

    DrawText("CONTROLS", SCREEN_WIDTH / 2 - MeasureText("CONTROLS", 50) / 2, 50, 50, textColor);
    DrawText("Up and Down Arrow Keys or W/S to cycle through the Menus", SCREEN_WIDTH / 2 - MeasureText("Up and Down Arrow Keys or W/S to cycle through the Menu", 20) / 2, 150, 20, textColor);
    DrawText("Enter to select", SCREEN_WIDTH / 2 - MeasureText("Enter to select", 20) / 2, 180, 20, textColor);

    // List of all controls
    DrawText("Game Controls:", 20, 230, 20, textColor);
    DrawText("- W: Player 1 Paddle Up", 50, 260, 20, textColor);
    DrawText("- S: Player 1 Paddle Down", 50, 290, 20, textColor);
    DrawText("- Up Arrow: Player 2 Paddle Up", 50, 320, 20, textColor);
    DrawText("- Down Arrow: Player 2 Paddle Down", 50, 350, 20, textColor);
    DrawText("- P: Pause Game", 50, 380, 20, textColor);
    DrawText("- M: Return to Main Menu", 50, 410, 20, textColor);
    DrawText("- R: Restart the Game", 50, 440, 20, textColor);
    DrawText("- D: Enter Double or Nothing Mode", 50, 470, 20, textColor);
    DrawText("- V: Open Settings", 50, 500, 20, textColor);
    DrawText("- C: Open Controls", 50, 530, 20, textColor);
    DrawText("- H: Toggle AI", 50, 560, 20, textColor);

    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M to return to Main Menu", 20) / 2, 575, 20, textColor);
    if (IsKeyPressed(KEY_M)) {// Returns to Main Menu
        if (sfxOn)
            PlaySound(soundManager.leaveMenu);
        gameState = 0;
    }
    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}
//                                                                                        -- Credits Screen --
void Credits(void)
{
        BeginDrawing();
        ClearBackground(bgColor);
    
        DrawText("CREDITS", SCREEN_WIDTH / 2 - MeasureText("CREDITS", 50) / 2, 60, 50, textColor);
    

        DrawText("Created, Designed and Coded By", SCREEN_WIDTH / 2 - MeasureText("Created, Designed and Coded By", 30) / 2, 140, 30, textColor);
        DrawText("Joseph Moore", SCREEN_WIDTH / 2 - MeasureText("Joseph Moore", 30) / 2, 180, 30, textColor);
    
        // Special Thanks
        DrawText("Special Thanks To:", SCREEN_WIDTH / 2 - MeasureText("Special Thanks To:", 25) / 2, 240, 25, textColor);
        DrawText("- The Raylib Community", SCREEN_WIDTH / 2 - 200, 300, 25, textColor);
        DrawText("- Anyone who tested or gave feedback", SCREEN_WIDTH / 2 - 200, 330, 25, textColor);
    
        // Return hint
        DrawText("Press M to return", SCREEN_WIDTH / 2 - MeasureText("Press M to return", 20) / 2, SCREEN_HEIGHT - 50, 20, textColor);
    
        if (showFPS) {
            DrawFPS(10, 20);
        }
        EndDrawing();
}

//                                                                                                   -- Modes Menu --
void DrawModesMenu(void)
{
    BeginDrawing();
    ClearBackground(bgColor);

    Color setupMode = (menuSelection == 0) ? textColor : GRAY;
    Color obstacleMode = (menuSelection == 1) ? textColor : GRAY;
    Color chaosMode = (menuSelection == 2) ? textColor : GRAY;

    DrawText("MODES", SCREEN_WIDTH / 2 - MeasureText("MODES", 50) / 2, 50, 50, textColor);
    DrawText("SET-UP PLAY", SCREEN_WIDTH / 2 - MeasureText("SET-UP PLAY", 40) / 2 + ((menuSelection == 0) ? selectionBounceModes.offset : 0), 225, 40, setupMode);
    DrawText("OBSTACLE MODE", SCREEN_WIDTH / 2 - MeasureText("OBSTACLE MODE", 40) / 2 + ((menuSelection == 1) ? selectionBounceModes.offset : 0), 300, 40, obstacleMode);
    DrawText("CHAOS MODE", SCREEN_WIDTH / 2 - MeasureText("CHAOS MODE", 40) / 2 + ((menuSelection == 2) ? selectionBounceModes.offset : 0), 375, 40, chaosMode);

    DrawText("Press Enter to Select", SCREEN_WIDTH / 2 - MeasureText("Press Enter to Select", 20) / 2, 550, 20, textColor);
    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M to return to Main Menu", 20) / 2, 575, 20, textColor);

    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}

// Function to Update Mode Selection
void UpdateModesMenu(void)
{
    UpdateSelectionHighlight(&selectionBounceModes);
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        menuSelection = (menuSelection + 1) % 3;
        StartSelectionBounce(&selectionBounceModes);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        menuSelection = (menuSelection - 1 + 3) % 3;
        StartSelectionBounce(&selectionBounceModes);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        if (sfxOn)
            PlaySound(soundManager.enterMenu);
        if (menuSelection == 0){
            ResetMenu();
            ResetScore();
            gameState = 8; // SET-UP PLAY
        }
        else if (menuSelection == 1) {
            gameState = 9; // OBSTACLE MODE 
            ResetScore();
            InitObstacles();
        }
        else if (menuSelection == 2)
            gameState = 10; // CHAOS MODE
            ResetScore();
            InitChaosMode();
    }

    if (IsKeyPressed(KEY_M)) {
        if (sfxOn)
            PlaySound(soundManager.enterMenu);
        gameState = 0;
    }
}
//                                                                                              -- SET UP PLAY - GAMESTATE = 8 --
void DrawSetupPlay(void)
{
    BeginDrawing();
    ClearBackground(bgColor);

    Color baseSpeedColor = (setUpSeclection == 0) ? textColor : GRAY;
    Color speedIncrementColor = (setUpSeclection == 1) ? textColor : GRAY;
    Color ballSizeColor = (setUpSeclection == 2) ? textColor : GRAY;
    Color PADDLE_HEIGHTColor = (setUpSeclection == 3) ? textColor : GRAY;
    Color PADDLE_SPEEDColor = (setUpSeclection == 4) ? textColor : GRAY;

    DrawText("SET-UP PLAY", SCREEN_WIDTH / 2 - MeasureText("SET-UP PLAY", 50) / 2, 50, 50, textColor);
    // SETUP PLAY SETTINGS
    DrawText(TextFormat("Base Speed: %.1f", baseSpeed), SCREEN_WIDTH / 2 - MeasureText("Base Speed: 3.0", 35) / 2 + ((setUpSeclection == 0) ? selectionBounceSetup.offset : 0), 275, 35, baseSpeedColor);
    DrawText(TextFormat("Speed Increment: %.2f", speedIncrement), SCREEN_WIDTH / 2 - MeasureText("Speed Increment: 1.00", 35) / 2 + ((setUpSeclection == 1) ? selectionBounceSetup.offset : 0), 325, 35, speedIncrementColor);
    DrawText(TextFormat("Ball Size: %.2f", BALL_SIZE), SCREEN_WIDTH / 2 - MeasureText("Ball Size: 30.00", 35) / 2 + ((setUpSeclection == 2) ? selectionBounceSetup.offset : 0), 375, 35, ballSizeColor);
    DrawText(TextFormat("Paddle Height: %.2f", PADDLE_HEIGHT), SCREEN_WIDTH / 2 - MeasureText("Paddle Height: 200.00", 35) / 2 + ((setUpSeclection == 3) ? selectionBounceSetup.offset : 0), 425, 35, PADDLE_HEIGHTColor);
    DrawText(TextFormat("Paddle Speed: %.2f", PADDLE_SPEED), SCREEN_WIDTH / 2 - MeasureText("Paddle Speed: 20.0", 35) / 2 + ((setUpSeclection == 4) ? selectionBounceSetup.offset : 0), 475, 35, PADDLE_SPEEDColor);    

    DrawText("Press Enter to Start", SCREEN_WIDTH / 2 - MeasureText("Press Enter to Start", 20) / 2, 550, 20, textColor);
    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M to return to Main Menu", 20) / 2, 575, 20, textColor);

    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}
void UpdateSetupPlay(void)
{
    UpdateSelectionHighlight(&selectionBounceSetup);
    const int setUpOptions = 5;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){ // Cycle through settings
        setUpSeclection = (setUpSeclection + 1) % setUpOptions;
        StartSelectionBounce(&selectionBounceSetup);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        setUpSeclection = (setUpSeclection - 1 + setUpOptions) % setUpOptions;
        StartSelectionBounce(&selectionBounceSetup);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (setUpSeclection == 0) // Base Speed
    {
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && baseSpeed > 3.0f)
            baseSpeed -= 0.5f;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && baseSpeed < 8.0f)
            baseSpeed += 0.5f;
    }
    else if (setUpSeclection == 1) // Speed Increment
    {
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && speedIncrement > 1.00f)
            speedIncrement -= 0.02f;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && speedIncrement < 1.30f)
            speedIncrement += 0.02f;
    }
    else if (setUpSeclection == 2) // Ball Size
    {
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && BALL_SIZE > 3.0f)
            BALL_SIZE -= 3.0f;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && BALL_SIZE < 30.0f)
            BALL_SIZE += 3.0f;
    }
    else if (setUpSeclection == 3) // Paddle Height
    {
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && PADDLE_HEIGHT > 50.0f)
            PADDLE_HEIGHT -= 10.0f;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && PADDLE_HEIGHT < 150.0f)
            PADDLE_HEIGHT += 10.0f;
    }
    else if (setUpSeclection == 4) // Paddle Speed
    {
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && PADDLE_SPEED > 1.0f)
            PADDLE_SPEED -= 1.0f;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && PADDLE_SPEED < 20.0f)
            PADDLE_SPEED += 1.0f;
    }
    if (IsKeyPressed(KEY_M))
    {
        if (sfxOn) {
            PlaySound(soundManager.leaveMenu);
        }
        gameState = 0;
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        if (sfxOn) {
            PlaySound(soundManager.enterMenu);
        }
        ResetScore();
        ResetGame();
    }
}
void quickPlaySelector(){

    UpdateSelectionHighlight(&selectionBounceQP);
    const int DifficultyOptions = 4;
    // Navigation
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        selectorSelection = (selectorSelection + 1) % DifficultyOptions;
        StartSelectionBounce(&selectionBounceQP);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        selectorSelection = (selectorSelection - 1 + DifficultyOptions) % DifficultyOptions;
        StartSelectionBounce(&selectionBounceQP);
        PlaySound(soundManager.menuNavigateVertical);
    }
    // Selection process
    if (IsKeyPressed(KEY_ENTER)){
        if (sfxOn) {
            PlaySound(soundManager.enterMenu);
        }
        gameState = 11; // Start the QuickPlay
        if (selectorSelection == 0) {
            aiDifficulty = DIFFICULTY_MEDIUM;
        } else if (selectorSelection == 1) {
            aiDifficulty = DIFFICULTY_HARD;
        } else if (selectorSelection == 2) {
            aiDifficulty = DIFFICULTY_CRACKED;
        } else if (selectorSelection == 3) {
            aiDifficulty = DIFFICULTY_EASY;
        }
    }
    if (IsKeyPressed(KEY_M)) {
        if (sfxOn) {
            PlaySound(soundManager.leaveMenu);
        }
        gameState = 0; // Return to Main Menu
    }
    BeginDrawing();
    ClearBackground(bgColor);
    DrawText("Quick Play", SCREEN_WIDTH / 2 - MeasureText("Quick Play", 50) / 2, 75, 50, textColor);
    DrawText("Gamble Safe", 10, 10, 20, darkMode ? LIGHTGRAY : DARKGRAY);

    Color mediumDiff = (selectorSelection == 0) ? textColor : GRAY;
    Color hardDiff = (selectorSelection == 1) ? textColor : GRAY;
    Color crackedDiff = (selectorSelection == 2) ? textColor : GRAY;
    Color easyDiff = (selectorSelection == 3) ? textColor : GRAY;

    DrawText("EASY", SCREEN_WIDTH / 2 - MeasureText("EASY", 35) / 2 + ((selectorSelection == 3) ? selectionBounceQP.offset : 0 ), 300, 35, easyDiff);
    DrawText("MEDIUM", SCREEN_WIDTH / 2 - MeasureText("MEDIUM", 35) / 2 + ((selectorSelection == 0) ? selectionBounceQP.offset : 0 ), 350, 35, mediumDiff);
    DrawText("HARD", SCREEN_WIDTH / 2 - MeasureText("HARD", 35) / 2 + ((selectorSelection == 1) ? selectionBounceQP.offset : 0 ), 400, 35, hardDiff);
    DrawText("CRACKED", SCREEN_WIDTH / 2 - MeasureText("CRACKED", 35) / 2 + ((selectorSelection == 2) ? selectionBounceQP.offset : 0 ), 450, 35, crackedDiff);

    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M to return to Main Menu", 20) / 2, 575, 20, textColor);
    if (showFPS) {
        DrawFPS(10, 30);
    }
    EndDrawing();
}