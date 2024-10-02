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
#include "raymath.h"
#include "screens.h"

/*Global Variables*/
#define MAX_BUILDINGS 100

//constant integers
const int screenWidth = 1700;
const int screenHeight = 1000;
static int framesCounter = 0;
static int finishScreen = 0;


//Bool Flags
bool CheckPoint_1 = false;
bool GameComplete = false;
// Updated player y position to keep it more centered vertically.

//Struct definitions
Rectangle player = { 400, 830, 40, 40 }; 
Rectangle buildings[MAX_BUILDINGS] = { 0 };
Color buildColors[MAX_BUILDINGS] = { 0 };
Camera2D camera = { 0 };

int spacing = 0;

float truerotation = 0.0f;

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    for (int i = 0; i < MAX_BUILDINGS; i++)
    {
        // Reduced height to ensure buildings are more visible.
        buildings[i].width = (float)GetRandomValue(50, 200);
        buildings[i].height = (float)GetRandomValue(100, 400); 
        buildings[i].y = screenHeight - 130.0f - buildings[i].height;
        buildings[i].x = spacing;

        spacing += (int)buildings[i].width;

        buildColors[i] = (Color){ GetRandomValue(200, 240), 
        GetRandomValue(200, 240), GetRandomValue(200, 250), 255 };
    }
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    SetTargetFPS(60);
    Camera2D camera = { 0 };
    camera.target = (Vector2)
    {
        player.x + player.width / 2.0f, player.y + player.height / 2.0f
    };
    camera.offset = (Vector2)
    {
        screenWidth / 2.0f, screenHeight / 2.0f
    };
    camera.rotation = 0.0f;
    camera.zoom = 0.8f; 

    if (IsKeyDown(KEY_RIGHT)) player.x += 2;
    else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

    // Camera target follows player
    camera.target = (Vector2){ player.x + 20, player.y + 20 };

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        if (GameComplete == true)
        {
            finishScreen = 1;
            PlaySound(fxCoin);
        }
        else
        {

        }
    }
}

/*Gameplay Section, where we do all our gameplay elements!*/
void DrawGameplayScreen(void)
{
    /*This sets the bounds of the camera.*/
    Camera2D camera = { 0 };
    
    camera.target = (Vector2)
    {
        player.x - 50.0f, player.y - 300.0f
    };
    camera.offset = (Vector2)
    {
        screenWidth / 2.0f, screenHeight / 2.0f
    };
    camera.rotation = 0.0f;
    camera.zoom = 0.8f; 

        /*We set our rotation to a true rotation
        variable, so that we can eventually snap back to
        proper place*/
        if (IsKeyDown(KEY_A))
        {
            truerotation -= 1.0f;
        }

        if (IsKeyDown(KEY_S))
        {
            truerotation += 1.0f;
        }
        
        camera.rotation = truerotation;
        
        BeginMode2D(camera);
   
    DrawRectangle(-6000, screenHeight - 130, 13000, 800, DARKGRAY);

    for (int i = 0; i < MAX_BUILDINGS; i++)
        DrawRectangleRec(buildings[i], buildColors[i]);

    DrawRectangleRec(player, RED);

    DrawText("SCREEN AREA", 20, 10, 20, RED);

    DrawRectangle(0, 0, 20, 5, RED);
    DrawRectangle(0, 5, 5, 20 - 10, RED);
    DrawRectangle(20 - 5, 5, 5, 20 - 10, RED);
    DrawRectangle(0, 20 - 5, 20, 5, RED);

    DrawRectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(10, 10, 250, 113, BLUE);

    DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
    DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
    DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
    DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

    if ((GameComplete == true) && (CheckPoint_1 == true))
    {
        DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 
                 130, 500, 50, PASTELPINK);
    }

    EndMode2D();
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