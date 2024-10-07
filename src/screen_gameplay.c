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

/*Global Defined Variables*/
#define MAX_BUILDINGS 100
#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

//constant integers
const int screenWidth = 1700;
const int screenHeight = 1000;
static int framesCounter = 0;
static int finishScreen = 0;


//Bool Flags
bool CheckPoint_1 = false;
bool GameComplete = false;
// Updated player y position to keep it more centered vertically.



//Building struct definitions
Rectangle buildings[MAX_BUILDINGS] = { 0 };
Color buildColors[MAX_BUILDINGS] = { 0 };

//Camera struct definitions
Camera2D camera = { 0 };


//Global Items Legnth condition. You want this global


int spacing = 0;

float truerotation = 0.0f;

typedef struct Player
{
    Vector2 position;
    float speed;
    bool canJump;
    int width;
    int x;
    int y;
    int height;
} Player;

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

//Items array



//Player Definitions
Player player = { 400, 830, 40, 40 }; 



/*Any Module Functions Go Here*/
void UpdatePlayer(
    Player *player, EnvItem *envItems, int envItemsLength, float delta);
void UpdateCameraCenter(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height);
void UpdateCameraOutOnLanding(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height);

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

    player.speed = 0;
    player.canJump = false;

    /*This should initialize the elements of platforms
    present. If not, we will tackle this problem later*/
    EnvItem envItems[] = {
    {{ 0, 0, 1000, 400 } , 0, LIGHTGRAY },
    {{ 0, 400, 1000, 200 } , 1, GRAY },
    {{ 300, 200, 400, 10 }, 1, GRAY},
    {{ 250, 300, 100, 10 }, 1, GRAY}
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);
}

/*Player call functions*/
void UpdatePlayer(
    Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }
    
    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + 1;
        Vector2 *p = &(player->position);
        if (ei->blocking && 
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y <= p->y + player->speed*delta)
        {
            hitObstacle = true;
            player->speed = 0.0f;
            p->y = ei->rect.y;
            break;
        }  
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
    
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

    if (IsKeyDown(KEY_SPACE))
    {

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
            if (truerotation < -40.0f) truerotation = -40.0f;
            
            
        }

        if (IsKeyDown(KEY_S))
        {
            truerotation += 1.0f;
            if (truerotation > 40.0f) truerotation = 40.0f;
        }
        
        camera.rotation = truerotation;
        
        BeginMode2D(camera);
   
    DrawRectangle(-6000, screenHeight - 130, 13000, 800, DARKGRAY);

    for (int i = 0; i < MAX_BUILDINGS; i++)
        DrawRectangleRec(buildings[i], buildColors[i]);

    Rectangle playerRect;
    DrawRectangleRec(playerRect, RED);

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

/*Camera update functions*/
void UpdateCameraCenter(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height)
{
    camera->offset = (Vector2) { width/2.0f, height/2.0f };
    camera->offset = (Vector2) { width/2.0f, height/2.0f };
    float mixX = 1000, minY = 1000, maxX = -1000, maxY = -1000;
}

void UpdateCameraCenterInsideMap(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }
    
    Vector2 max = GetWorldToScreen2D((Vector2) { maxX, maxY }, *camera);
    Vector2 min = GetWorldToScreen2D((Vector2) { minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = width/2 - min.x;
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y; 
}

void UpdateCameraCenterSmoothFollow(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(
            camera->target, Vector2Scale(diff, speed*delta/length));
    }
}

void UpdateCameraOutOnLanding(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target.x = player->position.x;
    
    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed*delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            } 
        }
        else
        {
            camera->target.y -= evenOutSpeed*delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
            
        }
        
    }
    else
    {
        camera->target.y -= evenOutSpeed*delta;

        if (camera->target.y < evenOutTarget)
        {
            camera->target.y = evenOutTarget;
            eveningOut = 0;
        }
    }
}

void UpdateCameraPlayerBoundsPush(
    Camera2D *camera, Player *player, EnvItem *envItems, 
    int envItemsLength, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2) { 
        (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height}, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2) {
        (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height}, *camera);
    camera->offset = (Vector2){ 
        (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.x < bboxWorldMin.x) 
    camera->target.x = player->position.x;

    if (player->position.y < bboxWorldMin.y) 
    camera->target.y = player->position.y;

    if (player->position.x > bboxWorldMax.x) 
    camera->target.x = bboxWorldMin.x + 
    (player->position.x - bboxWorldMax.x);
    
    if (player->position.y > bboxWorldMax.y) 
    camera->target.y = bboxWorldMin.y + 
    (player->position.y - bboxWorldMax.y);
}
