#include "ranlib.h"
#include "math.h"

#include "Tutorial.h"

#include "globals.h"
#include "GameLogic.h"
#include "SoundManager.h"
#include "SettingsMenu.h"
#include "AI.h"
#include "Custom.h"
#include "Menu.h"
#include "Animations.h"

int TutorialState = 0;


void UpdateTutorial(void)
{
    switch (TutorialState)
    {
    case 0: // Paddle Movement
        PaddleOneMovement();
        PaddleTwoMovement();
        break;
    case 1: // Hit The Ball
        PaddleOneMovement();
        PaddleTwoMovement();
        float BallSpeedX = 5.0f;
        ballX += ballSpeedX;
        if (ballX <= PADDLE_WIDTH && ballY + BALL_SIZE >= player1Y && ballY <= player1Y + PADDLE_HEIGHT)
        {
            ballSpeedX = -ballSpeedX;

        }
        if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - BALL_SIZE && ballY + BALL_SIZE >= player2Y && ballY <= player2Y + PADDLE_HEIGHT)
        {
            ballSpeedX = -ballSpeedX;
        }
        if (ballX <= 0 || ballX >= SCREEN_WIDTH - BALL_SIZE)
        {
            ResetBall();
        }
        break;
    case 2: // Hit The Ball With Paddle Corner (Goes until it hit a Wall then resets)
        BallMovement();
        PaddleOneMovement();
        PaddleTwoMovement();
        BallCollision();
        ScoringLogic();
        break;
    case 3: // Introduction to AI
        BallMovement();
        PaddleOneMovement();
        AICheck();
        BallCollision();
        ScoringLogic();
        break;
    case 4: // Try To Score a Point
        PaddleOneMovement();
        AICheck();
        BallMovement();
        BallCollision();
        ScoringLogic();
        if (player1Score == 2)
        {
            player1Score = 0;
        }
        break;
    case 5: // Tutorial Complete
        PaddleOneMovement();
        AICheck();
        BallMovement();
        BallCollision();
        ScoringLogic();
        break;
    }
    if (IsKeyPressed(KEY_SPACE)){
        TutorialState++;
        if (TutorialState > 5)
            TutorialState = 5;
        ResetBall();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) // Main Menu
    {
        TutorialState--;
        if (TutorialState < 0)
            TutorialState = 0;
    }
    if (IsKeyPressed(KEY_M)) // Main Menu
    {
        if (sfxOn)
            PlaySound(soundManager.leaveMenu);
        gameState = 0;
    }
}
void DrawTutorial(void)
{
    BeginDrawing();
    ClearBackground(bgColor);
    DrawText("TUTORIAL", SCREEN_WIDTH / 2 - MeasureText("TUTORIAL", 50) / 2, 100, 50, textColor);
    switch (TutorialState)
    {
    case 0: // Paddle Movement
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Use W/S to move your paddle || Player Two moves with UP/DOWN Keys", SCREEN_WIDTH / 2 
        - MeasureText("Use W/S to move your paddle || Player Two moves with UP/DOWN Keys", 20) / 2, SCREEN_HEIGHT / 2 - 30, 20, textColor);
        DrawPaddle();
        break;
    case 1: // Hit The Ball
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Press Backspace to go back", 10, 30, 20, textColor);
        DrawText("Use the paddle to hit the ball!", SCREEN_WIDTH / 2 
        - MeasureText("Use the paddle to hit the ball!", 20) / 2, SCREEN_HEIGHT / 2 - 30, 20, textColor);
        DrawPaddle();
        DrawBall();
        break;
    case 2: // Hit The Ball With Paddle Corner
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Press Backspace to go back", 10, 30, 20, textColor);
        DrawText("Now try to hit the ball on the corner of the paddle!", SCREEN_WIDTH / 2 
        - MeasureText("Now try to hit the ball on the corner of the paddle!", 20) / 2, SCREEN_HEIGHT / 2 - 30, 20, textColor);
        DrawText("Hitting the corner of the paddle sends the ball in that direction", SCREEN_WIDTH / 2 
        - MeasureText("Hitting the corner of the paddle sends the ball in that direction", 20) / 2, SCREEN_HEIGHT / 2 - 10, 20, textColor);
        DrawPaddle();
        DrawBall();
        break;
    case 3: // Introduction to AI
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Press Backspace to go back", 10, 30, 20, textColor);
        DrawText("AI will try to hit the ball back at you!", SCREEN_WIDTH / 2 
        - MeasureText("AI will try to hit the ball back at you!", 20) / 2, SCREEN_HEIGHT / 2 - 30, 20, textColor);
        DrawPaddle();
        DrawBall();
        break;
    case 4: // Try To Score a Point
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Press Backspace to go back", 10, 30, 20, textColor);
        DrawText("Try to score a point against the AI!", SCREEN_WIDTH / 2 
        - MeasureText("Try to score a point against the AI!", 20) / 2, SCREEN_HEIGHT / 2 - 30, 20, textColor);
        DrawText("You do this by hitting the ball into the opponents side", SCREEN_WIDTH / 2 
        - MeasureText("You do this by hitting the ball into the opponents side", 20) / 2, SCREEN_HEIGHT / 2 - 10, 20, textColor);
        DrawText(TextFormat("Player 1: %d", player1Score), SCREEN_WIDTH / 2, 20, 30, playerOne);
        DrawPaddle();
        DrawBall();
        break;
    case 5: // Tutorial Complete
        DrawText("Press Space to continue", 10, 10, 20, textColor);
        DrawText("Press Backspace to go back", 10, 30, 20, textColor);
        DrawText("Tutorial Complete! Be sure to check out the Controls.", SCREEN_WIDTH / 2 
        - MeasureText("Tutorial Complete! Be sure to check out the Controls.", 20) / 2, SCREEN_HEIGHT / 2 
        - 30, 20, textColor);
        DrawText("Press M to return to the Main Menu", SCREEN_WIDTH / 2 
        - MeasureText("Press M to return to the Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, textColor);
        DrawBall();
        DrawPaddle();
        DrawText(TextFormat("Player 1: %d", player1Score), SCREEN_WIDTH / 2, 20, 30, playerOne);
        DrawText(TextFormat("Player 2: %d", player2Score), SCREEN_WIDTH * 3 / 4 - 40, 20, 30, playerTwo);
        break;
    }
    EndDrawing();
}