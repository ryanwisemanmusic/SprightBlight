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

    SetTargetFPS(60); /*This could be done where we have
    FPS targetting based on system preference like in the 
    example of the Steam Deck*/
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 400, 500, 40, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
