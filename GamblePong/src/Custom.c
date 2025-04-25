#include "raylib.h"
#include "Custom.h"
#include "globals.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"

extern struct SoundManager soundManager;
extern bool showFPS, darkMode, musicOn, sfxOn, trailEffectOn, explosionEffectOn, backgroundEffectOn;
extern int customizationSelection;
extern Color bgColor, textColor;
extern const char* colorNames[];

extern int numColors;
extern int NUM_THEMES;
extern int themeIndex;
extern int playerOneIndex;
extern int playerTwoIndex;
extern int bgColorIndex;
extern int textColorIndex;
extern int ballColorIndex;
extern int obstacleColorIndex;
extern int trailColorIndex;
extern int explosionColorIndex;

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
extern Theme themes[];

void DrawCustomizationMenu(void)
{
    BeginDrawing();
    ClearBackground(bgColor);

    // Highlighted Selection
    Color selectionColor = textColor;
    Color nonSelectionColor = GRAY;

    DrawText("CUSTOMIZATION", SCREEN_WIDTH / 2 - MeasureText("CUSTOMIZATION", 50) / 2, 20, 50, textColor);

    // Predefined Themes
    Color themeColor = (customizationSelection == 0) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Theme: %s", themes[themeIndex].name), SCREEN_WIDTH / 2 - 140 + ((customizationSelection == 0) ? selectionBounceCustomization.offset : 0), 80, 35, themeColor);

    // Player 1 & Player 2 Colors
    Color labelColor = (customizationSelection == 1) ? selectionColor : nonSelectionColor;
    DrawText("Player Colors", SCREEN_WIDTH / 2 - MeasureText("Player Colors", 30) / 2 + ((customizationSelection == 1) ? selectionBounceCustomization.offset : 0), 130, 30, labelColor);

    // Player 1
    Color playerOneTextColor = (playerOne.r == bgColor.r && playerOne.g == bgColor.g && playerOne.b == bgColor.b) ? DARKGRAY : playerOne;
    DrawRectangle(SCREEN_WIDTH / 4 - 60, 180, 50, 50, playerOne);
    DrawRectangleLines(SCREEN_WIDTH / 4 - 60, 180, 50, 50, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    // p1 color box
    DrawText(colorNames[playerOneIndex], SCREEN_WIDTH / 4 - MeasureText(colorNames[playerOneIndex], 20) / 2, 240, 20, playerOneTextColor);

    // Draw smaller boxes for previous and next colors
    Color playerOnePrevColor = availableColors[(playerOneIndex - 1 + numColors) % numColors];
    Color playerOneNextColor = availableColors[(playerOneIndex + 1) % numColors];
    DrawRectangle(SCREEN_WIDTH / 4 - 110, 180, 30, 30, playerOnePrevColor);
    DrawRectangleLines(SCREEN_WIDTH / 4 - 110, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    DrawRectangle(SCREEN_WIDTH / 4 - -15, 180, 30, 30, playerOneNextColor);
    DrawRectangleLines(SCREEN_WIDTH / 4 - -15, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);

    Color playerOnePrevColor2 = availableColors[(playerOneIndex - 2 + numColors) % numColors];
    Color playerOneNextColor2 = availableColors[(playerOneIndex + 2) % numColors];
    DrawRectangle(SCREEN_WIDTH / 4 - 150, 180, 30, 30, playerOnePrevColor2);
    DrawRectangleLines(SCREEN_WIDTH / 4 - 150, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    DrawRectangle(SCREEN_WIDTH / 4 - -55, 180, 30, 30, playerOneNextColor2);
    DrawRectangleLines(SCREEN_WIDTH / 4 - -55, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);

    DrawTriangle( // Left Arrow
        (Vector2){SCREEN_WIDTH / 4 - 175, 205},
        (Vector2){SCREEN_WIDTH / 4 - 160, 215},
        (Vector2){SCREEN_WIDTH / 4 - 160, 195},
        textColor
    );

    DrawTriangle( // Right Arrow
        (Vector2){SCREEN_WIDTH / 4 + 110, 205},
        (Vector2){SCREEN_WIDTH / 4 + 95, 195},
        (Vector2){SCREEN_WIDTH / 4 + 95, 215},
        textColor
    );


    // Section divider
    for (int i = 170; i <= 460; i += 10) {
        DrawText("|", SCREEN_WIDTH / 2 - 5, i, 40, textColor);
    }

    // Player 2
    Color playerTwoTextColor = (playerTwo.r == bgColor.r && playerTwo.g == bgColor.g && playerTwo.b == bgColor.b) ? DARKGRAY : playerTwo;
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - 60, 180, 50, 50, playerTwo);
    DrawRectangleLines(SCREEN_WIDTH * 3 / 4 - 60, 180, 50, 50, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    // p2 color box
    DrawText(colorNames[playerTwoIndex], SCREEN_WIDTH * 3 / 4 - MeasureText(colorNames[playerTwoIndex], 20) / 2, 240, 20, playerTwoTextColor);

    // Draw smaller boxes for previous and next colors
    Color playerTwoPrevColor = availableColors[(playerTwoIndex - 1 + numColors) % numColors];
    Color playerTwoNextColor = availableColors[(playerTwoIndex + 1) % numColors];
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - 110, 180, 30, 30, playerTwoPrevColor);
    DrawRectangleLines(SCREEN_WIDTH * 3 / 4 - 110, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - -15, 180, 30, 30, playerTwoNextColor);
    DrawRectangleLines(SCREEN_WIDTH * 3 / 4 - -15, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);

    Color playerTwoPrevColor2 = availableColors[(playerTwoIndex - 2 + numColors) % numColors];
    Color playerTwoNextColor2 = availableColors[(playerTwoIndex + 2) % numColors];
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - 150, 180, 30, 30, playerTwoPrevColor2);
    DrawRectangleLines(SCREEN_WIDTH * 3 / 4 - 150, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);
    DrawRectangle(SCREEN_WIDTH * 3 / 4 - -55, 180, 30, 30, playerTwoNextColor2);
    DrawRectangleLines(SCREEN_WIDTH * 3 / 4 - -55, 180, 30, 30, (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) ? WHITE : BLACK);

    DrawTriangle( // Left Arrow
        (Vector2){SCREEN_WIDTH * 3 / 4 - 175, 205},
        (Vector2){SCREEN_WIDTH * 3 / 4 - 160, 215},
        (Vector2){SCREEN_WIDTH * 3 / 4 - 160, 195},
        textColor
    );

    DrawTriangle( // Right Arrow
        (Vector2){SCREEN_WIDTH * 3 / 4 + 110, 205},
        (Vector2){SCREEN_WIDTH * 3 / 4 + 95, 195},
        (Vector2){SCREEN_WIDTH * 3 / 4 + 95, 215},
        textColor
    );

    int baseX = 10;
    DrawText("- Color Settings -", baseX, 270, 35, textColor);

    // Text Color
    labelColor = (customizationSelection == 2) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Text: %s", colorNames[textColorIndex]), baseX + ((customizationSelection == 2) ? selectionBounceCustomization.offset : 0), 315, 25, labelColor);

    // Ball Color
    labelColor = (customizationSelection == 3) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Ball: %s", colorNames[ballColorIndex]), baseX + ((customizationSelection == 3) ? selectionBounceCustomization.offset : 0), 345, 25, labelColor);

    // Background Color
    labelColor = (customizationSelection == 4) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Background: %s", colorNames[bgColorIndex]), baseX + ((customizationSelection == 4) ? selectionBounceCustomization.offset : 0), 375, 25, labelColor);



    // Effect Colors
    DrawText("- Effect Colors -", SCREEN_WIDTH / 2 + 20, 270, 35, textColor);
    // Trail Color
    labelColor = (customizationSelection == 5) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Trail Color: %s", colorNames[trailColorIndex]), SCREEN_WIDTH / 2 + 10 + ((customizationSelection == 5) ? selectionBounceCustomization.offset : 0), 315, 25, labelColor);

    // Explosion Color
    labelColor = (customizationSelection == 6) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Explosion Color: %s", colorNames[explosionColorIndex]), SCREEN_WIDTH / 2 + 10 + ((customizationSelection == 6) ? selectionBounceCustomization.offset : 0), 345, 25, labelColor);

    // obstacle color
    labelColor = (customizationSelection == 7) ? selectionColor : nonSelectionColor;
    DrawText(TextFormat("Obstacle Color: %s", colorNames[obstacleColorIndex]), SCREEN_WIDTH / 2 + 10 + ((customizationSelection == 7) ? selectionBounceCustomization.offset : 0), 375, 25, labelColor);


    DrawText("Press M to return to Main Menu", SCREEN_WIDTH / 2 - 150, 575, 20, textColor);

    if (showFPS) {
        DrawFPS(10, 20);
    }
    EndDrawing();
}
// Update Customization
void UpdateCustomizationMenu(void)
{
    UpdateSelectionHighlight(&selectionBounceCustomization);
    const int customizationOptions = 8;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        customizationSelection = (customizationSelection + 1) % customizationOptions;
        StartSelectionBounce(&selectionBounceCustomization);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        customizationSelection = (customizationSelection - 1 + customizationOptions) % customizationOptions;
        StartSelectionBounce(&selectionBounceCustomization);
        PlaySound(soundManager.menuNavigateVertical);
    }
    if (IsKeyPressed(KEY_M)){
        if(sfxOn)
            PlaySound(soundManager.leaveMenu);
        gameState = 0; }

    switch (customizationSelection)
    {
        case 0: // Predefined Themes
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) themeIndex = (themeIndex - 1 + NUM_THEMES) % NUM_THEMES;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) themeIndex = (themeIndex + 1) % NUM_THEMES;
            ApplyTheme(themeIndex);
        case 1: // Player 1 & 2 Color Selection
            if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D))
            {
                playerOneIndex = (IsKeyPressed(KEY_A)) ? (playerOneIndex - 1 + numColors) % numColors : (playerOneIndex + 1) % numColors;
            }
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
            {
                playerTwoIndex = (IsKeyPressed(KEY_LEFT)) ? (playerTwoIndex - 1 + numColors) % numColors : (playerTwoIndex + 1) % numColors;
            }
            break;
        case 2: // Text Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) textColorIndex = (textColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) textColorIndex = (textColorIndex + 1) % numColors;
            break;
        case 3: // Ball Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) ballColorIndex = (ballColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) ballColorIndex = (ballColorIndex + 1) % numColors;
            break;
        case 4: // Background Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) bgColorIndex = (bgColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) bgColorIndex = (bgColorIndex + 1) % numColors;
            break;
        case 5: // Trail Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) trailColorIndex = (trailColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) trailColorIndex = (trailColorIndex + 1) % numColors;
            break;
        case 6: // Explosion Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) explosionColorIndex = (explosionColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) explosionColorIndex = (explosionColorIndex + 1) % numColors;
            break;
        case 7: // Obstacle Color
            if (IsKeyPressed(KEY_LEFT) || (IsKeyPressed(KEY_A))) obstacleColorIndex = (obstacleColorIndex - 1 + numColors) % numColors;
            if (IsKeyPressed(KEY_RIGHT) || (IsKeyPressed(KEY_D))) obstacleColorIndex = (obstacleColorIndex + 1) % numColors;
        break;
    }
    playerOne = availableColors[playerOneIndex];
    playerTwo = availableColors[playerTwoIndex];
    trailColor = availableColors[trailColorIndex];
    bgColor = availableColors[bgColorIndex];   
    ballColor = availableColors[ballColorIndex];
    textColor = availableColors[textColorIndex];
    explosionColor = availableColors[explosionColorIndex];
    obstacleColor = availableColors[obstacleColorIndex];
}
//                                  -- Themes
void ApplyTheme(int index) {

    Theme selectedTheme = themes[index];

    playerOneIndex = selectedTheme.playerOneColorIndex;
    playerTwoIndex = selectedTheme.playerTwoColorIndex;
    ballColorIndex = selectedTheme.ballColorIndex;
    bgColorIndex = selectedTheme.bgColorIndex;
    textColorIndex = selectedTheme.textColorIndex;
    trailColorIndex = selectedTheme.trailColorIndex;
    explosionColorIndex = selectedTheme.explosionColorIndex;
    obstacleColorIndex = selectedTheme.obstacleColorIndex;
}
