#include "raylib.h"
#include "SettingsMenu.h"
#include "globals.h"
#include "SoundManager.h"
#include "AI.h"

extern struct SoundManager soundManager;
extern bool showFPS, darkMode, musicOn, sfxOn, trailEffectOn, explosionEffectOn, backgroundEffectOn;
extern int settingsSelection;
extern Color bgColor, textColor;
extern const char *difficultyLevels[];
extern const char *aiPlaystyleNames[];
extern AIDifficulty aiDifficulty;
extern AIPlaystyle aiPlaystyle;
extern SelectionHighlight selectionBounceSettings;
extern int numPortals;

extern bool ObstacleMode;
extern bool PortalMode;
extern bool GravityFlip;
extern float GravityFlipTime; 
extern bool ColorFlip;
extern float ColorFlipStartTime;
extern float ColorFlipTime;
extern bool SpeedIncrease;
extern float SpeedIncreaseStartTime;
extern float SpeedIncreaseTime;
extern float chaosSpeedIncrease;
extern int BallType;
extern int OBSTACLEamount;
// Declare external functions
void UpdateSelectionHighlight(SelectionHighlight *highlight);
void StartSelectionBounce(SelectionHighlight *highlight);

void DrawSettingsMenu(void)
{
    BeginDrawing();
    ClearBackground(bgColor);
    DrawText("SETTINGS", SCREEN_WIDTH / 2 - MeasureText("SETTINGS", 50) / 2, 20, 50, textColor);

    Color selectionColor = textColor;
    Color nonSelectionColor = GRAY;

    // AI Settings
    Color difficultyColor = (settingsSelection == 0) ? selectionColor : nonSelectionColor;
    Color aiPlaystyleColor = (settingsSelection == 1) ? selectionColor : nonSelectionColor;

    // General Settings
    Color fpsColor = (settingsSelection == 2) ? selectionColor : nonSelectionColor;
    Color darkModeColor = (settingsSelection == 3) ? selectionColor : nonSelectionColor;
    Color ballTypeColor = (settingsSelection == 4) ? selectionColor : nonSelectionColor;

    // Music and SFX Toggles
    Color musicColor = (settingsSelection == 5) ? selectionColor : nonSelectionColor;
    Color sfxColor = (settingsSelection == 6) ? selectionColor : nonSelectionColor;

    // Modes
    Color obstacleToggleColor = (settingsSelection == 7) ? selectionColor : nonSelectionColor;
    Color obstacleColor = (ObstacleMode && settingsSelection == 8) ? selectionColor : nonSelectionColor;
    Color PortalToggleColor = (settingsSelection == 9) ? selectionColor : nonSelectionColor;
    Color PortalnumColor = (PortalMode && settingsSelection == 10) ? selectionColor : nonSelectionColor;
    Color gravityColor = (settingsSelection == 11) ? selectionColor : nonSelectionColor;
    Color gravityFlipFrequency = (GravityFlip && settingsSelection == 12) ? selectionColor : nonSelectionColor;
    Color colorFlipColor = (settingsSelection == 13) ? selectionColor : nonSelectionColor;
    Color colorFlipFrequency = (ColorFlip && settingsSelection == 14) ? selectionColor : nonSelectionColor;
    Color colorFlipDuration = (ColorFlip && settingsSelection == 15) ? selectionColor : nonSelectionColor;
    Color speedIncreaseColor = (settingsSelection == 16) ? selectionColor : nonSelectionColor;
    Color SpeedIncreaseStartTimeColor = (SpeedIncrease && settingsSelection == 17) ? selectionColor : nonSelectionColor;
    Color SpeedIncreaseDuration = (SpeedIncrease && settingsSelection == 18) ? selectionColor : nonSelectionColor;
    Color speedIncreaseAmount = (SpeedIncrease && settingsSelection == 19) ? selectionColor : nonSelectionColor;

    // effects toggles
    Color trailColor = (settingsSelection == 20) ? selectionColor : nonSelectionColor;
    Color explosionColor = (settingsSelection == 21) ? selectionColor : nonSelectionColor;
    Color bgEffectColor = (settingsSelection == 22) ? selectionColor : nonSelectionColor;


    int baseX = 10;

    DrawText("- AI -", baseX, 75, 35, textColor);

    DrawText(TextFormat("AI Difficulty: %s", difficultyLevels[aiDifficulty]), baseX + ((settingsSelection == 0) ? selectionBounceSettings.offset : 0), 115, 25, difficultyColor);
    DrawText(TextFormat("AI Playstyle: %s", aiPlaystyleNames[aiPlaystyle]), baseX + ((settingsSelection == 1) ? selectionBounceSettings.offset : 0), 145, 25, aiPlaystyleColor);

    DrawText("- General -", baseX, 200, 35, textColor);
    DrawText(TextFormat("Show FPS: %s", showFPS ? "ON" : "OFF"), baseX + ((settingsSelection == 2) ? selectionBounceSettings.offset : 0), 240, 25, fpsColor);
    DrawText(TextFormat("Dark Mode: %s", darkMode ? "ON" : "OFF"), baseX + ((settingsSelection == 3) ? selectionBounceSettings.offset : 0), 270, 25, darkModeColor);
    DrawText(TextFormat("Ball Type: %s", (BallType == 0) ? "Square" : "Round"), baseX + ((settingsSelection == 4) ? selectionBounceSettings.offset : 0), 300, 25, ballTypeColor);

    DrawText("- Sound -", baseX , 420, 35, textColor);
    DrawText(TextFormat("Music: %s", musicOn ? "ON" : "OFF"), baseX + ((settingsSelection == 5) ? selectionBounceSettings.offset : 0), 460, 25, musicColor);
    DrawText(TextFormat("Sound Effects: %s", sfxOn ? "ON" : "OFF"), baseX + ((settingsSelection == 6) ? selectionBounceSettings.offset : 0), 490, 25, sfxColor);

    // Divider Lines
    for (int i = 130; i <= 450; i += 10) {
        DrawText("|", SCREEN_WIDTH / 2 - 5, i, 40, textColor);
    }

    DrawText("- Modes -",  SCREEN_WIDTH / 2 + 20, 75, 35, textColor);
    DrawText(TextFormat("Obstacle %s", ObstacleMode ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 7) ? selectionBounceSettings.offset : 0), 115, 25, obstacleToggleColor);
    DrawText(TextFormat("- Obstacles Number: %d", OBSTACLEamount), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 8) ? selectionBounceSettings.offset : 0), 135, 20, obstacleColor);
    DrawText(TextFormat("Portal %s", PortalMode ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 9) ? selectionBounceSettings.offset : 0), 165, 25, PortalToggleColor);
    DrawText(TextFormat("- Portals Number: %d", numPortals), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 10) ? selectionBounceSettings.offset : 0), 185, 20, PortalnumColor);
    DrawText(TextFormat("Gravity Flip: %s", GravityFlip ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 11) ? selectionBounceSettings.offset : 0), 215, 25, gravityColor);
    DrawText(TextFormat("- Frequency: %.1fs", GravityFlipTime), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 12) ? selectionBounceSettings.offset : 0), 235, 20, gravityFlipFrequency);
    DrawText(TextFormat("Color Flip: %s", ColorFlip ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 13) ? selectionBounceSettings.offset : 0), 265, 25, colorFlipColor);
    DrawText(TextFormat("- Frequency: %.1fs", ColorFlipStartTime), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 14) ? selectionBounceSettings.offset : 0), 285, 20, colorFlipFrequency);
    DrawText(TextFormat("- Duration: %.1fs", ColorFlipTime), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 15) ? selectionBounceSettings.offset : 0), 305, 20, colorFlipDuration);
    DrawText(TextFormat("Speed Increase: %s", SpeedIncrease ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 16) ? selectionBounceSettings.offset : 0), 335, 25, speedIncreaseColor);
    DrawText(TextFormat("- Frequency: %.1fs", SpeedIncreaseStartTime), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 17) ? selectionBounceSettings.offset : 0), 355, 20, SpeedIncreaseStartTimeColor);
    DrawText(TextFormat("- Duration: %.1fs", SpeedIncreaseTime), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 18) ? selectionBounceSettings.offset : 0), 375, 20, SpeedIncreaseDuration);
    DrawText(TextFormat("- Increase Speed Multiplier: %.1fx", chaosSpeedIncrease), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 19) ? selectionBounceSettings.offset : 0), 395, 20, speedIncreaseAmount);

    DrawText("- Effects -", SCREEN_WIDTH / 2 + 20, 420, 35, textColor);
    DrawText(TextFormat("Trail Effect: %s", trailEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 20) ? selectionBounceSettings.offset : 0), 460, 25, trailColor);
    DrawText(TextFormat("Explosion Effect: %s", explosionEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 21) ? selectionBounceSettings.offset : 0), 490, 25, explosionColor);
    DrawText(TextFormat("Background Efect: %s", backgroundEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 22) ? selectionBounceSettings.offset : 0), 520, 25, bgEffectColor);

    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press M to return to Main Menu", 20) / 2, 575, 20, textColor);

    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}

// Update Settings Menu
void UpdateSettingsMenu(void)
{
    UpdateSelectionHighlight(&selectionBounceSettings);
    const int settingsOptions = 23;

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        do {
            settingsSelection = (settingsSelection + 1) % settingsOptions;
        } while ((settingsSelection == 8 && !ObstacleMode) ||
                 (settingsSelection == 10 && !PortalMode) ||
                 (settingsSelection == 12 && !GravityFlip) ||
                 (settingsSelection == 14 && !ColorFlip) ||
                 (settingsSelection == 15 && !ColorFlip) ||
                 (settingsSelection == 17 && !SpeedIncrease) ||
                 (settingsSelection == 18 && !SpeedIncrease) ||
                 (settingsSelection == 19 && !SpeedIncrease));
        
        StartSelectionBounce(&selectionBounceSettings);
        PlaySound(soundManager.menuNavigateVertical);
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        do {
            settingsSelection = (settingsSelection - 1 + settingsOptions) % settingsOptions;
        } while ((settingsSelection == 8 && !ObstacleMode) ||
                 (settingsSelection == 10 && !PortalMode) ||
                 (settingsSelection == 12 && !GravityFlip) ||
                 (settingsSelection == 14 && !ColorFlip) ||
                 (settingsSelection == 15 && !ColorFlip) ||
                 (settingsSelection == 17 && !SpeedIncrease) || 
                 (settingsSelection == 18 && !SpeedIncrease) ||
                 (settingsSelection == 19 && !SpeedIncrease));

        StartSelectionBounce(&selectionBounceSettings);
        PlaySound(soundManager.menuNavigateVertical);
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
        PlaySound(soundManager.menuNavigateHorizontal);
        switch (settingsSelection)
        {
        // AI Settings
        case 0:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                aiDifficulty = (AIDifficulty)((aiDifficulty - 1 + 4) % 4);
            } else {
                aiDifficulty = (AIDifficulty)((aiDifficulty + 1) % 4);
            }
            break;
        case 1:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                aiPlaystyle = (AIPlaystyle)((aiPlaystyle - 1 + 6) % 6);
            } else {
                aiPlaystyle = (AIPlaystyle)((aiPlaystyle + 1) % 6);
            }
            break;
        // General Settings
        case 2: showFPS = !showFPS; break;
        case 3: darkMode = !darkMode; break;
        case 4:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                BallType = (BallType - 1 + 2) % 2;
            } else {
                BallType = (BallType + 1) % 2;
            }
            break;
        // Music and SFX Toggles
        case 5: musicOn = !musicOn; break;
        case 6: sfxOn = !sfxOn; break;
        // Modes
        case 7: ObstacleMode = !ObstacleMode; break;
        case 8: 
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                OBSTACLEamount = (OBSTACLEamount - 1 + MAX_OBSTACLES) % MAX_OBSTACLES;
            } else {
                OBSTACLEamount = (OBSTACLEamount + 1) % MAX_OBSTACLES;
            }
            break;
        case 9: PortalMode = !PortalMode; break;
        case 10:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                numPortals = (numPortals - 1 + MAX_PORTALS) % MAX_PORTALS;
            }
            else {
                numPortals = (numPortals + 1) % MAX_PORTALS;
            }
            break;
        case 11: GravityFlip = !GravityFlip; break;
        case 12:
        if (GravityFlip) {
            GravityFlipTime += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.5f : 0.5f;
            if (GravityFlipTime < 0.5f) GravityFlipTime = 0.5f;
        }
        break;
            break;
        case 13: ColorFlip = !ColorFlip; break;
        case 14:
        if (ColorFlip) {
            ColorFlipStartTime += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.5f : 0.5f;
            if (ColorFlipStartTime < 0.5f) ColorFlipStartTime = 0.5f;
        }
        break;
        case 15:
            if (ColorFlip) {
                ColorFlipStartTime += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.5f : 0.5f;
                if (ColorFlipStartTime < 0.5f) ColorFlipStartTime = 0.5f;
            }
            break;
        case 16: SpeedIncrease = !SpeedIncrease; break;
        case 17:
            if (SpeedIncrease) {
                SpeedIncreaseStartTime += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.5f : 0.5f;
                if (SpeedIncreaseStartTime < 0.5f) SpeedIncreaseStartTime = 0.5f;
            }
        case 18:
            if (SpeedIncrease) {
                SpeedIncreaseTime += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.5f : 0.5f;
                if (SpeedIncreaseTime < 0.5f) SpeedIncreaseTime = 0.5f;
            }
            break;
        case 19:
            if (SpeedIncrease) {
                chaosSpeedIncrease += (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) ? -0.1f : 0.1f;
                if (chaosSpeedIncrease < 1.0f) chaosSpeedIncrease = 1.0f;
            }
            break;
        // Effects Toggles
        case 20: trailEffectOn = !trailEffectOn; break;
        case 21: explosionEffectOn = !explosionEffectOn; break;
        case 22: backgroundEffectOn = !backgroundEffectOn; break;
        }
    }
    if (darkMode) {
        bgColor = BLACK;
        textColor = WHITE;
    } else {
        bgColor = availableColors[bgColorIndex];
        textColor = availableColors[textColorIndex];
    }
    if (IsKeyPressed(KEY_M)){
        if (sfxOn)
            PlaySound(soundManager.leaveMenu);
        gameState = 0;
    }
}