#include "raylib.h"
#include <math.h>

#include "include/globals.h"
#include "include/GameLogic.h"
#include "include/SoundManager.h"
#include "include/SettingsMenu.h"
#include "include/AI.h"
#include "include/Custom.h"
#include "include/Menu.h"
#include "include/Animations.h"
#include "include/Tutorial.h"


void InitGame();
void CloseGame();

void InitGame() {
    // Initialize game customized variables
    ApplyTheme(themeIndex);
    InitAudioDevice();
    LoadSounds(&soundManager);

    playerOne = availableColors[playerOneIndex];
    playerTwo = availableColors[playerTwoIndex];
    bgColor = availableColors[bgColorIndex];
    ballColor = availableColors[ballColorIndex];
    textColor = availableColors[textColorIndex];

    obstacleColor = availableColors[obstacleColorIndex];
    portalColor = availableColors[portalColorIndex];
    trailColor = availableColors[trailColorIndex];
    explosionColor = availableColors[explosionColorIndex];

    paddle1Color = playerOne;
    paddle2Color = playerTwo;
}

int main(void)
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gamble Pong");
    SetTargetFPS(60);

    InitGame();
    ResetBall();

    LoadSounds(&soundManager);
    // Main Game Loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
        {
            paused = !paused;
        }
        // Pause Game Controlls
        if (paused && IsKeyPressed(KEY_M))
        {
            gameState = 0;
            paused = false;
            RevertColors();
            ResetMenu();
        }
        // Game States
        switch (gameState)
        {
        case 0:
            UpdateTitleScreen(); // TITLE SCREEN
            DrawTitleScreen(); // TITLE SCREEN
            MainMenuAIGame();
            DrawAIGame();
            break;
        case 1:
            if (!paused)
                UpdateGame();
            DrawGameScreen();
        case 4:
            if (!paused)
                UpdateGame(); // DOUBLE OR NOTHING
            DrawGameScreen();
            break;
        case 2:
            DrawPostGameMenu("Player 1 Wins!"); // POST GAME MENU PLAYER1WINS
            HandlePostGameOptions();
            break;
        case 3:
            DrawPostGameMenu("Player 2 Wins!"); // POST GAME MENU PLAYER2WINS
            HandlePostGameOptions();
            break;
        case 5:
            if (!isSettingsMenuLoaded) {
                settingsSelection = 0; 
                isSettingsMenuLoaded = true;
            }
            UpdateSettingsMenu(); // SETTINGS MENU
            DrawSettingsMenu();
            break;
        case 6:
            DrawControlsScreen(); // CONTROLS SCREEN
            break;
        case 7:
            if (!isModesMenuLoaded) {
                menuSelection = 0;
                isModesMenuLoaded = true;
            }
            UpdateModesMenu(); // MODES MENU SCREEN
            DrawModesMenu();
            break;
        case 8:
            if (!isSettingsMenuLoaded) {
                settingsSelection = 0; 
                isSettingsMenuLoaded = true;
            }
            UpdateSetupPlay(); // SET-UP PLAY
            DrawSetupPlay();
            break;
        case 9:
            if (!paused) {
                UpdateGame(); // OBSTACLE MODE
                UpdateObstacles();
            }
            DrawGameScreen();
            DrawObstacles();
            break;
        case 10:
            if (!paused) {
                UpdateGame(); // CHAOS MODE
                UpdateChoasMde();
            }
            DrawGameScreen();
            DrawPortals();
            DrawObstacles();
            DrawGravityFlip();

            break;
        case 11:
            if (!paused)
                UpdateQuickPlay(); // QUICK PLAY
            DrawQuickPlay();
            break;
        case 12:
            UpdateCustomizationMenu();
            DrawCustomizationMenu(); // CUSTOMIZATION MENU
            break;
        case 13:
            Credits(); // CREDITS SCREEN
            break;
        case 14: // QuickPlaySelector
            quickPlaySelector();
            break;
        case 15: // TUTORIAL
            UpdateTutorial();
            DrawTutorial();
            break;
        }
    }
    if (gameState == 0) {
        isSettingsMenuLoaded = false;
        isModesMenuLoaded = false;
    }
    CloseAudioDevice();
    CloseGame();
    CloseWindow();
    return 0;
}

void CloseGame() {
    UnloadSounds(&soundManager);    // Unload sounds
    CloseAudioDevice();     // Close audio device
}
