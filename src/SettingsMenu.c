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
    Color obstacleColor = (settingsSelection == 7) ? selectionColor : nonSelectionColor;
    Color PortalnumColor = (settingsSelection == 8) ? selectionColor : nonSelectionColor;
    Color gravityColor = (settingsSelection == 9) ? selectionColor : nonSelectionColor;
    Color colorFlipColor = (settingsSelection == 10) ? selectionColor : nonSelectionColor;
    Color speedIncreaseColor = (settingsSelection == 11) ? selectionColor : nonSelectionColor;
    Color speedIncreaseAmount = (settingsSelection == 12) ? selectionColor : nonSelectionColor;

    // effects toggles
    Color trailColor = (settingsSelection == 13) ? selectionColor : nonSelectionColor;
    Color explosionColor = (settingsSelection == 14) ? selectionColor : nonSelectionColor;
    Color bgEffectColor = (settingsSelection == 15) ? selectionColor : nonSelectionColor;


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
    DrawText(TextFormat("Max Obstacles: %d", OBSTACLEamount), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 7) ? selectionBounceSettings.offset : 0), 115, 25, obstacleColor);
    DrawText(TextFormat("Max Portals: %d", numPortals), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 8) ? selectionBounceSettings.offset : 0), 145, 25, PortalnumColor);
    DrawText(TextFormat("Gravity Flip: %s", GravityFlip ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 9) ? selectionBounceSettings.offset : 0), 175, 25, gravityColor);
    DrawText(TextFormat("Color Flip: %s", ColorFlip ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 10) ? selectionBounceSettings.offset : 0), 205, 25, colorFlipColor);
    DrawText(TextFormat("Speed Increase: %s", SpeedIncrease ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 11) ? selectionBounceSettings.offset : 0), 235, 25, speedIncreaseColor);
    DrawText(TextFormat("- Speed Increase Amount: %.2f", chaosSpeedIncrease), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 12) ? selectionBounceSettings.offset : 0), 265, 20, speedIncreaseAmount);

    DrawText("- Effects -", SCREEN_WIDTH / 2 + 20, 420, 35, textColor);
    DrawText(TextFormat("Trail Effect: %s", trailEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 13) ? selectionBounceSettings.offset : 0), 460, 25, trailColor);
    DrawText(TextFormat("Explosion Effect: %s", explosionEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 14) ? selectionBounceSettings.offset : 0), 490, 25, explosionColor);
    DrawText(TextFormat("Background Efect: %s", backgroundEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 15) ? selectionBounceSettings.offset : 0), 520, 25, bgEffectColor);

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
    const int settingsOptions = 16;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        settingsSelection = (settingsSelection + 1) % settingsOptions;
        StartSelectionBounce(&selectionBounceSettings);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        settingsSelection = (settingsSelection - 1 + settingsOptions) % settingsOptions;
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
        case 7: 
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                OBSTACLEamount = (OBSTACLEamount - 1 + MAX_OBSTACLES) % MAX_OBSTACLES;
            } else {
                OBSTACLEamount = (OBSTACLEamount + 1) % MAX_OBSTACLES;
            }
            break;
        case 8:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                numPortals = (numPortals - 1 + MAX_PORTALS) % MAX_PORTALS;
            }
            else {
                numPortals = (numPortals + 1) % MAX_PORTALS;
            }
            break;
        case 9: GravityFlip = !GravityFlip; break;
        case 10: ColorFlip = !ColorFlip; break;
        case 11: SpeedIncrease = !SpeedIncrease; break;
        case 12:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                chaosSpeedIncrease = (chaosSpeedIncrease - 0.1f < 0.1f) ? 0.1f : chaosSpeedIncrease - 0.1f;
            } else {
                chaosSpeedIncrease += 0.1f;
            }
            break;
        // Effects Toggles
        case 13: trailEffectOn = !trailEffectOn; break;
        case 14: explosionEffectOn = !explosionEffectOn; break;
        case 15: backgroundEffectOn = !backgroundEffectOn; break;
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