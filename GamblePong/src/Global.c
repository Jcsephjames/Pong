#include "globals.h"
#include "raylib.h"
#include "SoundManager.h"
#include "GameLogic.h"
#include "SettingsMenu.h"

SoundManager soundManager;

SoundManager sm;

bool isSettingsMenuLoaded = false;
bool isModesMenuLoaded = false;
int gameState = 0;
// const char *gameStateNames[] = {"Main Menu", "Game", "Modes", "Customization", "Settings", "Controls", "Credits", "Quick Play", "Setup Play", "Obstacle Mode", "Chaos Mode"};
int menuSelection = 0;
int settingsSelection = 0;
int setUpSeclection = 0;
int selectorSelection = 0;
bool paused = false;

int BallType = 0; // 0 = Standard Square, 1 = Round Ball, 3 = Triangle Ball

float MAX_BALLSPEED = 10.0f;

// AI and Difficulty
bool AIEnabled = true;
float aiSpeed;
float reactionBuffer = 0;
float offset = 0;
float player1LastHits[5];
int hitIndex = 0;
const char *difficultyLevels[] = {"Easy", "Medium", "Hard", "Cracked"};
AIDifficulty aiDifficulty = DIFFICULTY_MEDIUM;
const char *aiPlaystyleNames[] = {"Mixed", "Defensive", "Offensive", "Tricky", "Adaptive", "Random"};
AIPlaystyle aiPlaystyle = PLAYSTYLE_MIXED;
AIPlaystyle chosenRandomStyle = PLAYSTYLE_MIXED;

// QUICKPLAY VARIABLES
float baseSpeedQUICK = 5.0f;
float speedIncrementQUICK = 1.10f;
float currentSpeedMultiplierQUICK = 1.0f;

// Explosion Variables
float explosionPower = 1.4f;

// CHOAS MODE
// Portals
float portalCooldown = 0.0f;
Portal portals[MAX_PORTALS];
int numPortals = 3;
int portalAmount = 1;

// OBSTACLE VARIABLES
int OBSTACLEamount = 4;

// GameChangableVariables
float speedIncrement = 1.05f;
float PADDLE_SPEED = 5.0f;

// Settings Variables
bool musicOn = true;
bool sfxOn = true;
bool showFPS = false;
bool darkMode = false;
bool trailEffectOn = false;
bool explosionEffectOn = true;
bool backgroundEffectOn = true;

// CUSTOMISED MENU
int customizationSelection = 0;
Color availableColors[] = {BLACK, WHITE, RED, BLUE, PINK, PURPLE, GREEN, ORANGE, SKYBLUE, LIME, MAROON, GOLD,
                             {173, 255, 47, 255}, {255, 105, 180, 255}, {0, 255, 255, 255}, DARKBLUE, {255, 69, 0, 255}};
const char* colorNames[] = {"BLACK", "WHITE", "RED", "BLUE", "PINK", "PURPLE", "GREEN", "ORANGE", "SKYBLUE", "LIME", "MAROON", "GOLD",
                             "GREENYELLOW", "HOTPINK", "CYAN", "DARKBLUE", "REDORANGE"};
int numColors = sizeof(availableColors) / sizeof(availableColors[0]);

// Themes and the Struct
int NUM_THEMES = 8;
// typedef struct {
//     const char *name;
//     int playerOneColorIndex;
//     int playerTwoColorIndex;
//     int ballColorIndex;
//     int bgColorIndex;
//     int textColorIndex;
//     int trailColorIndex;
//     int explosionColorIndex;
//     int obstacleColorIndex;
//     int portalColorIndex;
// } Theme; 0 = Black, 1 = White, 2 = Red, 3 = Blue, 4 = Pink, 5 = Purple, 6 = Green, 7 = Orange, 8 = SkyBlue, 9 = Lime, 10 = Maroon, 11 = Gold
//          12 = GreenYellow, 13 = HotPink, 14 = Cyan, 15 = DarkBlue, 16 = RedOrange
Theme themes[] = {
    {"Default", 2, 3, 0, 1, 0, 2, 9, 0, 0},
    {"OnOcustom", 5, 9, 11, 0, 5, 2, 9, 13, 5},
    {"Old Arcade", 6, 6, 6, 0, 6, 2, 6, 6, 1},
    {"Retro", 10, 11, 11, 1, 0, 10, 7, 9, 1},
    {"Neon", 7, 6, 6, 0, 1, 7, 7, 9, 0},
    {"Ocean", 12, 14, 9, 3, 9, 8, 7, 3, 3},
    {"Forest", 6, 5, 5, 2, 5, 6, 7, 6, 0},
    {"Fire", 4, 3, 3, 1, 0, 4, 7, 2, 1}
};
// Color Indexes
int themeIndex = 0;
int playerOneIndex = 2;
int playerTwoIndex = 3;
int bgColorIndex = 1;
int textColorIndex = 0;
int ballColorIndex = 0;
int obstacleColorIndex = 0;
int trailColorIndex = 2;
int explosionColorIndex = 0;
int portalColorIndex = 0;


// Stored color variables
Color playerOne;
Color playerTwo;
Color paddle1Color;
Color paddle2Color;
Color bgColor;
Color ballColor;
Color textColor;
Color headingsColor;
Color portalColor;
Color obstacleColor;
Color trailColor;
Color explosionColor;

// Title Screen Animations
Vector2 bgBallPos = {400, 300};
Vector2 bgBallSpeed = {5.0f, 3.0f};  
Rectangle aiPaddleLeft = { 30, 250, 10, 100 };
Rectangle aiPaddleRight = { 760, 250, 10, 100 };

SelectionHighlight selectionBounceMenu = { 0, false, 0.0f, 30, 45.0f }; // 30 frames, 45px dash
SelectionHighlight selectionBounceSettings = { 0, false, 0.0f, 25, 30.0f }; // 30 frames, 45px dash
SelectionHighlight selectionBounceModes = { 0, false, 0.0f, 30, 45.0f }; // 10 frames, 40px dash
SelectionHighlight selectionBounceSetup = { 0, false, 0.0f, 30, 45.0f }; // 10 frames, 40px dash
SelectionHighlight selectionBounceCustomization = { 0, false, 0.0f, 30, 45.0f }; // 10 frames, 40px dash
SelectionHighlight selectionBounceQP= { 0, false, 0.0f, 30, 45.0f }; // 10 frames, 40px dash