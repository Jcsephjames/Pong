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

    // Modes
    Color obstacleColor = (settingsSelection == 4) ? selectionColor : nonSelectionColor;

    // Music and SFX Toggles
    Color musicColor = (settingsSelection == 5) ? selectionColor : nonSelectionColor;
    Color sfxColor = (settingsSelection == 6) ? selectionColor : nonSelectionColor;
    // effects toggles
    Color trailColor = (settingsSelection == 7) ? selectionColor : nonSelectionColor;
    Color explosionColor = (settingsSelection == 8) ? selectionColor : nonSelectionColor;
    Color bgEffectColor = (settingsSelection == 9) ? selectionColor : nonSelectionColor;


    int baseX = 10;

    DrawText("- AI -", baseX, 75, 35, textColor);

    DrawText(TextFormat("AI Difficulty: %s", difficultyLevels[aiDifficulty]), baseX + ((settingsSelection == 0) ? selectionBounceSettings.offset : 0), 115, 25, difficultyColor);
    DrawText(TextFormat("AI Playstyle: %s", aiPlaystyleNames[aiPlaystyle]), baseX + ((settingsSelection == 1) ? selectionBounceSettings.offset : 0), 145, 25, aiPlaystyleColor);

    DrawText("- General -", baseX, 200, 35, textColor);
    DrawText(TextFormat("Show FPS: %s", showFPS ? "ON" : "OFF"), baseX + ((settingsSelection == 2) ? selectionBounceSettings.offset : 0), 240, 25, fpsColor);
    DrawText(TextFormat("Dark Mode: %s", darkMode ? "ON" : "OFF"), baseX + ((settingsSelection == 3) ? selectionBounceSettings.offset : 0), 270, 25, darkModeColor);
    
    DrawText("- Modes -", baseX, 330, 35, textColor);
    DrawText(TextFormat("Max Obstacles: %d", OBSTACLEamount),baseX + ((settingsSelection == 4) ? selectionBounceSettings.offset : 0), 370, 25, obstacleColor);
    // Divider Lines
    for (int i = 130; i <= 450; i += 10) {
        DrawText("|", SCREEN_WIDTH / 2 - 5, i, 40, textColor);
    }

    DrawText("- Sound -", SCREEN_WIDTH / 2 + 20, 75, 35, textColor);
    DrawText(TextFormat("Music: %s", musicOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 5) ? selectionBounceSettings.offset : 0), 115, 25, musicColor);
    DrawText(TextFormat("Sound Effects: %s", sfxOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 20 + ((settingsSelection == 6) ? selectionBounceSettings.offset : 0), 145, 25, sfxColor);


    DrawText("- Effects -", SCREEN_WIDTH / 2 + 20, 330, 35, textColor);
    DrawText(TextFormat("Trail Effect: %s", trailEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 7) ? selectionBounceSettings.offset : 0), 370, 25, trailColor);
    DrawText(TextFormat("Explosion Effect: %s", explosionEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 8) ? selectionBounceSettings.offset : 0), 400, 25, explosionColor);
    DrawText(TextFormat("Background Efect: %s", backgroundEffectOn ? "ON" : "OFF"), SCREEN_WIDTH / 2 + 10 + ((settingsSelection == 9) ? selectionBounceSettings.offset : 0), 430, 25, bgEffectColor);

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
    const int settingsOptions = 10;
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
        // Modes
        case 4: 
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
                OBSTACLEamount = (OBSTACLEamount - 1 + MAX_OBSTACLES) % MAX_OBSTACLES;
            } else {
                OBSTACLEamount = (OBSTACLEamount + 1) % MAX_OBSTACLES;
            }
            break;
        // Music and SFX Toggles
        case 5: musicOn = !musicOn; break;
        case 6: sfxOn = !sfxOn; break;
        // Effects Toggles
        case 7: trailEffectOn = !trailEffectOn; break;
        case 8: explosionEffectOn = !explosionEffectOn; break;
        case 9: backgroundEffectOn = !backgroundEffectOn; break;
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