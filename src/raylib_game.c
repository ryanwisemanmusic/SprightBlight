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
// NOTE: Declares global (extern) variables and screens functions
#include "screens.h"    

/*We include some web headers so that
this game translates to the internet.*/
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
GameScreen currentScreen = LOGO;
Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

// Local Variables Definition (local to this module)
static const int screenWidth = 800;
static const int screenHeight = 450;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

/*Local Functions Declarations are here:*/

// Change to screen, no transition effect
static void ChangeToScreen(int screen);     
// Request transition to next screen
static void TransitionToScreen(int screen); 
// Update transition effect
static void UpdateTransition(void);         
// Draw transition effect (full-screen rectangle)
static void DrawTransition(void);           
// Update and draw one frame
static void UpdateDrawFrame(void);         

/*The main function*/
int main(void)
{
    /*This draws the game to be 1700 by 1000. Currently,
    this is the resolution I want set for editing, as
    full screen implementation seems like a tricky ass
    thing to do*/
    const int screenWidth = 1700;
    const int screenHeight = 1000;

    /*This is our basic window, which we name so if we
    have to */
    InitWindow(screenWidth, screenHeight, 
    "raylib [core] example - basic window");
    GameScreen currentScreen = LOGO;

    /*We initialize framesCounter to zero
    for the sake of when we rerun said code*/
    int framesCounter = 0;

    SetTargetFPS(60); /*This could be done where we have
    FPS targetting based on system preference like in the 
    example of the Steam Deck*/
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (currentScreen)
        {
        case LOGO:
        {
        //TODO: Logic for screen here

        framesCounter++;

        /*After 120 frames of the logo animation,
        go to title*/
            if (framesCounter > 120)
            {
                currentScreen = TITLE;
            } 
        } break;
        
        /*Anything we want to put in our title
        logic goes here. This would be a great
        place for a Title Screen menu, which'll
        be implemented eventually*/
        case TITLE:
            {
                if (IsKeyPressed(KEY_ENTER) || 
                IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;

        /*Any of our gameplay logic will go here, which is
        gonna be a very large function in the end.*/
        case GAMEPLAY:
        {
            if (IsKeyPressed(KEY_ENTER) || 
            IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = ENDING;
            }
            
        } break;

        /*When we complete the game, this will
        be any ending credit logic. This would
        be great for if I were to have a huge
        team working on the project. What we
        will store here are any sound credits.*/
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER) ||
            IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = TITLE;
            }
            
        } break;
        /*Since we will never be in default, we
        just allow this sectio to break. I 
        could be wrong about what goes here, though*/
        default:
            break;
        }

        BeginDrawing();
        
        /*We use a switch statement to cycle through different windows.
        This will be a good chunk of the logic needed for the codebase.*/
        switch (currentScreen)
        {
        case LOGO:
            {
                DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                DrawText("Wait for 2 seconds..." , 290, 220, 20, GRAY);
            } break;
        case TITLE:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN",
            120, 220, 20, DARKGREEN);
        } break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, PINK);
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAGENTA);
            DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN",
            120, 220, 20, DARKGREEN);
        } break;
        case ENDING:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 
            120, 220, 20, DARKBLUE);
        }
        default:
            break;
        }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
