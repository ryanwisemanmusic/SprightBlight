/************************************************************************
*   <Spright Blight>
*   <Bullet hell spright game>
*
*   This game was created via raylib,
*   Credit to raysan5 for designing this incredible engine
*
*   Copyright (c) 2024 - Ryan Wiseman
************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    #define MAX_BUILDINGS 100
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        const int screenWidth = 1700;
        const int screenHeight = 1000;

        bool Complete = false;

        Rectangle player = { 400, 280, 40, 40};
        Rectangle buildings[MAX_BUILDINGS] = { 0 };
        Color buildColors[MAX_BUILDINGS] = { 0 };

        int spacing = 0;

        for (int i = 0; i < MAX_BUILDINGS; i++)
        {
            buildings[i].width = (float)GetRandomValue(50, 200);
            buildings[i].x = -6000.0f + spacing;

            spacing += (int)buildings[i].width;

            buildColors[i] = (Color)
            {
                GetRandomValue(200, 240), GetRandomValue(200, 240),
                GetRandomValue(200,250), 255
            };
        }

        Camera2D camera = { 0 };
        camera.target = (Vector2)
        {
            player.x + 20.0f, player.y + 20.0f
        };
        camera.offset = (Vector2)
        {
            screenWidth/2.0f, screenHeight/2.0f
        };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);

        for (int i = 0; i < MAX_BUILDINGS; i++) 
        DrawRectangleRec(buildings[i], buildColors[i]);

        DrawRectangleRec(player, RED);

        DrawLine((int)camera.target.x, -screenHeight*10, 
        (int)camera.target.x, screenHeight*10, GREEN);
        DrawLine(-screenWidth*10, (int)camera.target.y, 
        screenWidth*10, (int)camera.target.y, GREEN);

        EndMode2D;

        DrawText("SCREEN AREA", 640, 10, 20, RED);

            DrawRectangle(0, 0, screenWidth, 5, RED);
            DrawRectangle(0, 5, 5, screenHeight - 10, RED);
            DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, RED);
            DrawRectangle(0, screenHeight - 5, screenWidth, 5, RED);

            DrawRectangle( 10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 250, 113, BLUE);

            DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
            DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
            DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);
        
        EndDrawing();

        Complete = true;
        bool StatusCheck = false;
        
        /*This should be the logic for end game state.
        As we only allow us to reach the endscreen
        by completing the game, this means that are code
        before it needs to be all the fun game logic*/
        if (Complete = true)
        {
            if (StatusCheck = true)
            {
                finishScreen = 1;
                PlaySound(fxCoin);
            }
            else
            {
                finishScreen = 0;
            }

        }
        
    }
    
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{

    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(
        font, "GAMEPLAY SCREEN", pos, font.baseSize*8.0f, 4, COLDPURPLE);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 
    130, 500, 50, PASTELPINK);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}