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

/*We include some web headers so that
this game translates to the internet.*/
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h

GameScreen currentScreen = LOGO;
Font font = { 0 };
Music musicTitle = { 0 };
Music musicGameplayLvl1_01 = { 0 };
Music musicEnding = { 0 };
Sound fxCoin = { 0 };

static float currentVolume = 1.0f; 

// Local Variables Definition (local to this module)
static const int screenWidth = 1700;
static const int screenHeight = 1000;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

/*Any local funcitons will go here*/
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

/*Our main function*/
int main(void)
{
    //Initialize the window
    InitWindow(screenWidth, screenHeight, "raylib game template");
    //Initialize audio
    InitAudioDevice();  

    /*Global Asset Storage Place. Will be modifying the program to
    use my own audio assets.*/
    font = LoadFont("resources/mecha.png");
    musicTitle = LoadMusicStream("resources/Eventide.wav");
    musicGameplayLvl1_01 = 
    LoadMusicStream("resources/gameplay_soundtrack_01.wav");
    musicEnding = LoadMusicStream("resources/DrunkenSunsets.wav");
    fxCoin = LoadSound("resources/coin.wav");

    /*This allows us to set the volume of our music and play it*/
    SetMusicVolume(musicTitle, currentVolume);
    SetMusicVolume(musicGameplayLvl1_01, currentVolume);
    SetMusicVolume(musicGameplayLvl1_01, currentVolume);
    PlayMusicStream(musicTitle);

    // Setup and init first screen
    currentScreen = LOGO;
    InitLogoScreen();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60); /*This could be done where we have
    FPS targetting based on system preference like in the 
    example of the Steam Deck*/

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateDrawFrame();
    }

#endif
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case GAMEPLAY: 
        UnloadGameplayScreen(); 
        break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }
    
    // Unload global data loaded
    UnloadFont(font);
    UnloadMusicStream(musicTitle);
    UnloadMusicStream(musicGameplayLvl1_01);
    UnloadMusicStream(musicEnding);
    UnloadSound(fxCoin);

    /*Close audio*/
    CloseAudioDevice();
    /*Close Window and OpenGL use*/
    CloseWindow();
    return 0;
}

// Module specific Functions Definition
// Change to next screen, no transition
static void ChangeToScreen(GameScreen screen)
{
    if (currentScreen == GAMEPLAY && !IsMusicStreamPlaying(musicGameplayLvl1_01)) {
    PlayMusicStream(musicGameplayLvl1_01);
}
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;

        case GAMEPLAY: 
        UnloadGameplayScreen(); 
        StopMusicStream(musicTitle);
        break;

        case ENDING: 
        UnloadEndingScreen(); 
        
        break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: 
        InitLogoScreen(); 
        break;

        case TITLE: InitTitleScreen(); break;
        case GAMEPLAY: InitGameplayScreen(); 
        PlayMusicStream(musicGameplayLvl1_01);
        break;

        case ENDING: InitEndingScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        /*NOTE: Due to float internal representation, 
        condition jumps on 1.0f instead of 1.05f*/
        /*For that reason we compare against 1.01f, 
        to avoid last frame loading stop*/ 
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case OPTIONS: UnloadOptionsScreen(); break;
                case GAMEPLAY: UnloadGameplayScreen(); break;
                case ENDING: UnloadEndingScreen(); break;
                default: break;
                
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: InitLogoScreen(); break;
                case TITLE: InitTitleScreen(); break;
                case GAMEPLAY: InitGameplayScreen(); break;
                case ENDING: InitEndingScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), 
    GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
    /*Audio logic for all the draw frames.*/
    if ((currentScreen == LOGO) || (currentScreen == TITLE))
        UpdateMusicStream(musicTitle);
    
    if (currentScreen == GAMEPLAY)
        UpdateMusicStream(musicGameplayLvl1_01);
    
    if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                UpdateLogoScreen();

                if (FinishLogoScreen()) TransitionToScreen(TITLE);
            } break;

            case TITLE:
            {
                UpdateTitleScreen();
                if (FinishTitleScreen() == 1) 
                TransitionToScreen(OPTIONS);
                else if (FinishTitleScreen() == 2) 
                TransitionToScreen(GAMEPLAY);
            } break;

            case OPTIONS:
            {
                UpdateOptionsScreen();

                if (FinishOptionsScreen()) TransitionToScreen(TITLE);
            } break;

            case GAMEPLAY:
            {
                UpdateGameplayScreen();
                if (FinishGameplayScreen() == 1) TransitionToScreen(ENDING);
            //else if (FinishGameplayScreen() == 2) TransitionToScreen(TITLE);
            } break;

            case ENDING:
            {
                StopMusicStream(musicGameplayLvl1_01);
                UpdateEndingScreen();

                if (FinishEndingScreen() == 1) TransitionToScreen(TITLE);

            } break;
            default: break;
        }
    }
    // Update transition (fade-in, fade-out)
    else UpdateTransition();    
    

    /*How we draw with the GPU*/
    BeginDrawing();
    ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOGO: DrawLogoScreen(); break;
            case TITLE: DrawTitleScreen(); break;
            case OPTIONS: DrawOptionsScreen(); break;
            case GAMEPLAY: DrawGameplayScreen(); break;
            case ENDING: DrawEndingScreen(); break;
            default: break;
        }

        // Draw full screen rectangle in front of everything
        if (onTransition) DrawTransition();

        //DrawFPS(10, 10);

    EndDrawing();
}