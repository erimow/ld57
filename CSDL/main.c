//
//  main.c
//  CSDL
//
//  Created by Erik Morris on 7/16/24.
//

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "Engine/constants.h"
#include "Engine/Texture.h"
#include "Engine/Button.h"
#include "Engine/Timer.h"
#include "Engine/Camera.h"
#include "Engine/Entity.h"
#include "Engine/BackgroundEntity.h"
#include "Engine/Tilemap.h"


/* Important stuff */
const int ticksPerFrame = 1000.0f/TARGET_FPS;
SDL_Window * window = NULL; //freed
SDL_Renderer* renderer = NULL; //freed

/* Textures/Fonts */
TTF_Font * gFont = NULL; //freed
Texture fontTexture; //freed

Texture fpsTexture; //freed

/* Entities */
Entity player; //freed
Entity testObject; //freed

Entity fish; //freed
BackgroundEntity bgFish; //freed

/* Other */
Button butt; //freed
SDL_Joystick * gamePad = NULL; //freed
Timer fps; //no need to free
Timer capTimer;
int frameCount = 0;

Camera camera; //freed

/* TILE MAP */
Texture tilemapSpriteSheet; // Freed by tilemap
Tilemap tilemap; // freed

/* Music/Sounds */
Mix_Chunk* soundEffect = NULL; //freed
Mix_Music* gameMusic = NULL; //freed




bool loadMedia(void)
{
    bool success = true;
    
    //initialize everything!
    //Texture_init(&test);
    Texture_init(&fontTexture);
    Texture_init(&fpsTexture);
    Texture_init(&tilemapSpriteSheet);
    Timer_init(&fps);
    Timer_init(&capTimer);
    Button_init(&butt, 0, 0, 125, 75);
    //Entity_init(&player, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, 100, 10);  //Normal entity init
    Entity_initPhysics(&player, SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2-50, 100, 100, 0.8f, 12.0f, 0.3f, .95f, 8.0f, 3);
    Entity_initPhysics(&testObject, 300, -1000, 100, 100, .8f, 12.0f, 0.3f, .95f, 8.0f, 1);
    Entity_init(&fish, 300, 300, 100, 100, 0.0, 2);
    
    Camera_init(&camera);
    
    if (!Texture_loadFromFile(&tilemapSpriteSheet, renderer, "TileSpritesheet.png"))
    {
        printf("Failed to load TileSpritesheet texture image!\n");
        success = false;
    }
    Tilemap_init(&tilemap, &tilemapSpriteSheet, "/Users/erik/Documents/Projects/CSDL/CSDL/CSDL/map.txt");

    if (!Entity_setTexture(&player, renderer, "StarfishSpriteSheet.png"))
    {
        printf("Failed to load Starfish.png texture image!\n");
        success = false;
    }
    player.clip[0] = (SDL_Rect){2, 5, 25, 22};
    player.clip[1] = (SDL_Rect){34, 5, 25, 22};
    player.clip[2] = (SDL_Rect){66, 5, 25, 22};

    if (!Entity_setTexture(&testObject, renderer, "RelicArt.png"))
    {
        printf("Failed to load RelicArt.png!\n");
        success=false;
    }
    
    if (!Entity_setTexture(&fish, renderer, "BackgroundFishSpriteSheet.png"))
    {
        printf("Failed to load background fish!\n");
        success=false;
    }
    fish.clip[0] = (SDL_Rect){0,0,32,32};
    fish.clip[1] = (SDL_Rect){32,0,32,32};
    BackgroundEntity_init(&bgFish, &fish, 8); // CURRENTLY NEED TO INIT AFTER LOADING ENTITY TEXTURE. NEED TO MAKE ENTITY'S TEXTURE A POINTER DONT FORGET
    
    gFont = TTF_OpenFont("/System/Library/Fonts/Noteworthy.ttc", 56); //Location and font size;
    if(gFont!= NULL){
        SDL_Color fontCol= {0, 255, 122, 255};
        if(!Texture_loadFromRenderedText(&fontTexture, renderer, gFont, "Starfish Adventures the Epilogue", fontCol))
        {
            printf("Failed to load Font texture!\n");
            success = false;
        }
        fontCol.g = 0; fontCol.b = 0; fontCol.r = 0;
        if (!Button_loadTextures(&butt, renderer, "ButtonBackground.png", "Music", gFont, fontCol))
        {
            printf("Failed to load button texture!\n");
            success = false;
        }
        
    }
    soundEffect = Mix_LoadWAV("low.wav");
    if(soundEffect == NULL)
    {
        printf("Could not set soundEffect sound! Error: %s\n", Mix_GetError());
    }
//    gameMusic = Mix_LoadMUS("Sounds/game - music 1.wav");
    gameMusic = Mix_LoadMUS("The Penguin God.wav");
    if(gameMusic == NULL)
    {
        printf("Could not set gameMusic! Error: %s\n", Mix_GetError());
    }
    
    return success;
}


/*------------------------------------ GAME LOOP ----------------------------------*/

void gameloop(void){
    Timer_start(&fps);
    SDL_FRect fpsLoc = {SCREEN_WIDTH-50,0,50,25};
    SDL_Color fpsCol = {0,0,0,255};
    Texture_setColor(&player.spriteSheet, 10, 255, 10);
    
    Uint8 currentPlayerSprite=0;
    
    //Camera_setCameraOffset(&camera, 0, -200);
    float cameraOffsetX, cameraOffsetY;
    
    
    
    //Scene Objects
    int sceneObjectAmount = 5;
    SDL_FRect sceneObjects[sceneObjectAmount];
    SDL_FRect boxA = {800, 500, 100, 100}; sceneObjects[0]=boxA;
    SDL_FRect groundA = {0, 700, SCREEN_WIDTH, 25}; sceneObjects[1] = groundA;
    SDL_FRect objA = {600, 500, 50, 125}; sceneObjects[2] = objA;
    SDL_FRect headbutA = {200, 375, 300, 75}; sceneObjects[3] = headbutA;
    
    
    //player stuff
    double playerRotation = 0.0;
    bool onNub = false;
    bool lastMovedRight = false;

    
    bool isButtPressed = false;
    
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        Timer_start(&capTimer);
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            Button_handleEvent(&butt, &e, &isButtPressed);
            Entity_handleEvent(&player, &e);
        }
        
        if (Mix_PlayingMusic() == 0)
        {
            if (isButtPressed)
            {
                Mix_PlayMusic(gameMusic, -1);
            }
        }
        else
        {
            if (!isButtPressed && (Mix_PausedMusic()==0))
            {
                Mix_PauseMusic();
            }
            else if (isButtPressed && Mix_PausedMusic()==1)
            {
                Mix_ResumeMusic();
            }
        }
        
        // ACTUAL GAME STUFF
        bool checkForLanding = false;
        if (player.onGround==0)
            checkForLanding = true;
        Entity_move(&player, sceneObjects, sceneObjectAmount);
        if (player.onGround == 1 && checkForLanding){
            Mix_PlayChannel(-1, soundEffect, 0);
            playerRotation += player.xVel/2;
        }
        else if (player.onGround == 1)
            playerRotation += player.xVel/2;
        Entity_move(&testObject, sceneObjects, 4);
        Camera_followEntity(&camera, &player);
        Camera_getObjectOffset(&camera, &cameraOffsetX, &cameraOffsetY);
        
        sceneObjects[4] = testObject.collider;

        
        
        SDL_FRect box = {800-cameraOffsetX, 500-cameraOffsetY, 100, 100};
        SDL_FRect ground = {0-cameraOffsetX, 700-cameraOffsetY, SCREEN_WIDTH, 25};
        SDL_FRect obj = {600-cameraOffsetX, 500-cameraOffsetY, 50, 125};
        SDL_FRect headbut = {200-cameraOffsetX, 375-cameraOffsetY, 300, 75};
        
        
        //player rotation stuff
        if (player.xVel>0) {lastMovedRight=true;} else if (player.xVel<0) {lastMovedRight=false;}
        
        if ((((int)playerRotation%360 <-195 && (int)playerRotation%360 > -270) || ((((int)playerRotation%360 >90 && (int)playerRotation%360 < 165)))) && !lastMovedRight && player.onGround){
            if (!onNub){
                currentPlayerSprite = 1;
                onNub = true;
            }}
        else if((((int)playerRotation%360 >100 && (int)playerRotation%360 < 180) || ((((int)playerRotation%360 <-180 && (int)playerRotation%360 > -260)))) && lastMovedRight && player.onGround){
            if (!onNub){
                currentPlayerSprite = 2;
                onNub = true;
            }
        }
        else{
                currentPlayerSprite = 0;
                onNub = false;
        }
        Entity_setRotation(&player, playerRotation);
        //end player rotation stuff
        
        
        // FPS Stuff
        Uint32 avgFps = frameCount/(Timer_getTicks(&fps)/1000.f);
        char fpsText[50];
        snprintf(fpsText, sizeof(fpsText), "fps: %d", avgFps); //Feeds int into char buffer
        
        // START OF RENDERING
        SDL_SetRenderDrawColor( renderer, 100, 200, 255, 0xFF );
        SDL_RenderClear(renderer);
        
        // OBJECT RENDERING
        //Texture_render(&test, renderer, NULL, &imageLoc, 0.0, NULL, SDL_FLIP_NONE);
        BackgroundEntity_update(&bgFish, renderer, cameraOffsetX, cameraOffsetY, frameCount, 30);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x11, 0, 0xFF);
        SDL_RenderFillRectF(renderer, &box);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x11, 0, 0xFF);
        SDL_RenderFillRectF(renderer, &obj);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x11, 0, 0xFF);
        SDL_RenderFillRectF(renderer, &ground);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x11, 0, 0xFF);
        SDL_RenderFillRectF(renderer, &headbut);
        
        Tilemap_render(&tilemap, renderer, cameraOffsetX, cameraOffsetY);
        
        Entity_render(&testObject, renderer, &player.clip[0], -1, NULL,  SDL_FLIP_NONE, cameraOffsetX, cameraOffsetY);
       
        Entity_render(&player, renderer, NULL, currentPlayerSprite, NULL, SDL_FLIP_NONE, cameraOffsetX, cameraOffsetY);
        
        
        //UI RENDERING
        if (!Texture_loadFromRenderedText(&fpsTexture, renderer, gFont, fpsText, fpsCol))
        {
            printf("Couldn't render fps text!!\n");
        }
        else
        {
            Texture_render(&fpsTexture,renderer, NULL, &fpsLoc, 0.0, NULL, SDL_FLIP_NONE);
        }
        Button_render(&butt, renderer);
        
        //printf("%f\n",camera.yPos);   PRINT CAMERA POS
        
        // RENDER
        SDL_RenderPresent(renderer);
        frameCount++;
        
        //FPS CAP
        int frameTicks = Timer_getTicks(&capTimer);
        if (frameTicks < ticksPerFrame)
        {
            SDL_Delay(ticksPerFrame - frameTicks);
        }
    }
}

/*---------------------------------- END GAME LOOP ----------------------------------*/


bool init(void){
    bool success = false;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |SDL_INIT_JOYSTICK)<0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else{
       
        window = SDL_CreateWindow("Erik test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window was not loaded! SDL Error : %s\n", SDL_GetError());
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                printf("Renderer was not loaded! SDL Error : %s\n", SDL_GetError());
            }
            else
            {
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
                }
                
                else{
                    //Init audio stuff
                    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                    {
                        printf("Mix could not init! SDL_Mix Error: %s\n", Mix_GetError());
                    }
                    else
                    {
                        //Initialize SDL_ttf
                        if( TTF_Init() == -1 )
                        {
                            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        }
                        else
                        {
                            //LOAD MEDIA
                            if (!loadMedia())
                            {
                                printf("Could not load texture image!\n");
                            }
                            else{
                                //CHECK FOR JOYSTICKS AND SET TEXTURE FILTERING
                                
                                //Set texture filtering to linear
                                if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
                                {
                                    printf( "Warning: Linear texture filtering not enabled!" );
                                }
                                
                                //Check for joysticks
                                if( SDL_NumJoysticks() < 1 )
                                {
                                    printf( "Warning: No joysticks connected!\n" );
                                }
                                else
                                {
                                    //Load joystick
                                    gamePad = SDL_JoystickOpen( 0 );
                                    if( gamePad == NULL )
                                    {
                                        printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
                                    }
                                }
                                success = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return success;
}

void quit(void)
{
    Tilemap_free(&tilemap);
    
    Texture_free(&fontTexture);
    //Texture_free(&test);
    Texture_free(&fpsTexture);
    Entity_free(&testObject, true);
    Entity_free(&player, true);
    Entity_free(&fish, true);
    BackgroundEntity_free(&bgFish);
    Camera_free(&camera);
    TTF_CloseFont(gFont);
    gFont = NULL;
    gamePad = NULL;
    Mix_FreeChunk(soundEffect);
    Mix_FreeMusic(gameMusic);
    soundEffect = NULL;
    gameMusic = NULL;
    Button_free(&butt);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char * argv[])
{
    srand((unsigned int)time(NULL));
    if (!init())
        printf("Init not loaded properly!");
    else
    {
        gameloop();
    }
    quit();

    return 0;
}

