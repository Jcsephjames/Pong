#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include "globals.h"
#include "SoundManager.h"
#include "GameLogic.h"

// GAME Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 10
#define MAX_PARTICLES 100
#define MAX_OBSTACLES 15
#define MAX_PORTALS 10

extern SoundManager soundManager;
// Game Variables

typedef struct Paddle {
    float y;
    float speed;
    int score;
} Paddle;

typedef struct Ball {
    float x, y;
    float speedX, speedY;
    float baseSpeed;
    float radius;
} Ball;

typedef struct Game {
    int state;
    int lastScorer;
    float speedMultiplier;
    bool aiEnabled;
    int aiDifficulty;
    int playstyle;
} Game;

typedef struct Particle {
    Vector2 position;
    float lifespan;
    Color color;
} Particle;

extern bool isSettingsMenuLoaded;
extern bool isModesMenuLoaded;
extern int gameState;
extern const char *gameStateNames[];
extern int player1Score, player2Score;
extern int lastScorer;
extern int menuSelection;
extern int settingsSelection;
extern int setUpSeclection;
extern int selectorSelection;
extern bool paused;
extern float player1Y, player2Y;
extern float ballX, ballY, ballSpeedX, ballSpeedY;
extern float currentSpeedMultiplier;

extern Ball ball;
extern Paddle player1, player2;
extern Game game;
extern float BALL_SIZE, PADDLE_HEIGHT, speedIncrement, MAX_BALLSPEED;

typedef struct {
    Vector2 position;
    Vector2 size;
    bool active;

        // Movement data
    bool isMoving;
    float startY;
    float endY;
    bool movingDown;
} Obstacle;
Obstacle obstacles[MAX_OBSTACLES];
extern int numObstacles;
extern int OBSTACLEamount;

// CHAOSE MODE
// Portals
typedef struct Portal {
    Vector2 position1;
    Vector2 position2;
    Vector2 size;
    Color color;
    bool isActive;
} Portal;
#define MAX_PORTALS 10
extern Portal portals[MAX_PORTALS];
extern float portalCooldown;
extern int numPortals;
extern int portalAmount;
extern float chaosSpeedIncrease;

// Gravity Flip
extern float GravityFlipTimer;
// AI and Difficulty
extern bool AIEnabled;
extern float aiSpeed;
extern float reactionBuffer;
extern float offset;
extern float player1LastHits[5];
extern int hitIndex;
extern bool randomStyleChosen;
extern const char *difficultyLevels[];
extern const char *aiPlaystyleNames[];
extern int BallType;

// Define AIDifficulty enum
typedef enum {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD,
    DIFFICULTY_CRACKED
} AIDifficulty;

// Define AIPlaystyle enum
typedef enum {
    PLAYSTYLE_MIXED,
    PLAYSTYLE_DEFENSIVE,
    PLAYSTYLE_OFFENSIVE,
    PLAYSTYLE_TRICKY,
    PLAYSTYLE_ADAPTIVE,
    PLAYSTYLE_RANDOM
} AIPlaystyle;

extern AIDifficulty aiDifficulty;
extern AIPlaystyle aiPlaystyle;

// QUICKPLAY VARIABLES
extern float baseSpeedQUICK;
extern float speedIncrementQUICK;
extern float currentSpeedMultiplierQUICK;
extern float BALL_SIZEQUICK;
extern float PADDLE_HEIGHTQUICK;

// Explosion Variables
extern float explosionPower;

// GameChangableVariables
extern float baseSpeed;
extern float speedIncrement;
extern float BALL_SIZE;
extern float PADDLE_HEIGHT;
extern float PADDLE_SPEED;

// Settings Variables
extern bool musicOn;
extern bool sfxOn;
extern bool showFPS;
extern bool darkMode;
extern bool trailEffectOn;
extern bool explosionEffectOn;
extern bool backgroundEffectOn;
extern bool GravityFlip;
extern bool ColorFlip;
extern bool SpeedIncrease;
extern float chaosSpeedIncrease;

// CUSTOMISED MENU
extern int customizationSelection;
extern Color availableColors[];
extern const char* colorNames[];
extern int numColors;

// Theme
extern int themeIndex;
extern int playerOneIndex;
extern int playerTwoIndex;
extern int bgColorIndex;
extern int textColorIndex;
extern int ballColorIndex;
extern int obstacleColorIndex;
extern int portalColorIndex;
extern int trailColorIndex;
extern int explosionColorIndex;

// Stored color variables
extern Color playerOne;
extern Color playerTwo;
extern Color paddle1Color;
extern Color paddle2Color;
extern Color bgColor;
extern Color ballColor;
extern Color textColor;
extern Color headingsColor;
extern Color obstacleColor;
extern Color trailColor;
extern Color explosionColor;
extern Color portalColor;

// Theme struct

typedef struct {
    const char *name;
    int playerOneColorIndex;
    int playerTwoColorIndex;
    int ballColorIndex;
    int bgColorIndex;
    int textColorIndex;
    int trailColorIndex;
    int explosionColorIndex;
    int obstacleColorIndex;
    int portalColorIndex;
} Theme;
extern Theme themes[];

// Menu Animation Variables
typedef struct {
    int frames;
    bool animating;
    float offset;
    int maxFrames;
    float dashDistance;
} SelectionHighlight;
 extern SelectionHighlight selectionBounceSettings;
 extern SelectionHighlight selectionBounceSetup;
 extern SelectionHighlight selectionBounceModes;
 extern SelectionHighlight selectionBounceMenu;
 extern SelectionHighlight selectionBounceCustomization;
 extern SelectionHighlight selectionBounceQP;


// Title Screen Animations
extern Vector2 bgBallPos;
extern Vector2 bgBallSpeed;
extern Rectangle aiPaddleLeft;
extern Rectangle aiPaddleRight;

// Particle System
typedef struct ExplosionParticle {
    Vector2 position;
    Vector2 velocity;
    float lifespan;
    Color color;
} ExplosionParticle;

ExplosionParticle particles[MAX_PARTICLES];

extern int particleCount;

#endif // GLOBALS_H