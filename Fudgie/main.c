//
//  main.c
//  CSDL
//
//  Created by Erik Morris on 7/16/24.
//

// #include "Engine/BackgroundEntity.h"
// #include "Engine/Button.h"
// #include "Engine/Camera.h"
// #include "Engine/Entity.h"
// #include "Engine/Texture.h"
// #include "Engine/Tilemap.h"
//#include "Engine/Timer.h"
#include "Engine/constants.h"
#include "Engine/context.h"
#include "Scripts/game.c"
//#include <SDL2/SDL.h>
#include <SDL3/SDL.h>
#ifdef __linux__
//#include <SDL/SDL_image.h>
//#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_pixels.h>
//#include <SDL2/SDL_rect.h>
//#include <SDL2/SDL_render.h>
//#include <SDL2/SDL_ttf.h>
#elif defined __APPLE__
// #include <SDL2_image/SDL_image.h>
// #include <SDL2_mixer/SDL_mixer.h>
// #include <SDL2_ttf/SDL_ttf.h>
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif /* ifdef __EMSCRIPTEN__ */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool loadMedia(context *ctx) {
  bool success = true;

  // Texture_init(&ctx->fontTexture);
  // Texture_init(&ctx->fpsTexture);
  // Timer_init(&ctx->fps);
  // Timer_init(&ctx->capTimer);
  // Button_init(&ctx->butt, 10, 10, 25, 25);
  // Entity_init(&player, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, 100, 10);
  // //Normal entity init

  // ctx->gFont = TTF_OpenFont("Fonts/tuffy_regular.ttf",
  //                           56); // Location and font size;
  // if (ctx->gFont != NULL) {
  //   SDL_Color fontCol = {0, 255, 122, 255};
  //   if (!Texture_loadFromRenderedText(&ctx->fontTexture, ctx->renderer,
  //                                     ctx->gFont, "Fudgie", fontCol)) {
  //     printf("Failed to load Font texture!\n");
  //     success = false;
  //   }
  //   fontCol.g = 0;
  //   fontCol.b = 0;
  //   fontCol.r = 0;
  //   if (!Button_loadTextures(&ctx->butt, ctx->renderer,
  //                            "Art/ButtonBackground.png", "Music", ctx->gFont,
  //                            fontCol)) {
  //     printf("Failed to load button texture!\n");
  //     success = false;
  //   }
  // }
  // ctx->soundEffect = Mix_LoadWAV("Sounds/low.wav");
  // if (ctx->soundEffect == NULL) {
  //   printf("Could not set soundEffect sound! Error: %s\n", Mix_GetError());
  // }
  // //    gameMusic = Mix_LoadMUS("Sounds/game - music 1.wav");
  // ctx->gameMusic = Mix_LoadMUS("Sounds/The Penguin God.wav");
  // if (ctx->gameMusic == NULL) {
  //   printf("Could not set gameMusic! Error: %s\n", Mix_GetError());
  // }

  printf("Done loading media\n");
  return success;
}

// START GAME LOOP
void startGameloop(context *ctx) {
  // Timer_start(&ctx->fps);
  Game_Start(ctx);
}

void gameLoop(void *arg) {
  context *ctx = SDL_static_cast(context *, arg);
  // Timer_start(&ctx->capTimer);
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    Game_Events(ctx, &e); // Calls the events function in the game file
#ifdef __EMSCRIPTEN__
    if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_END) {
        emscripten_cancel_main_loop();
      }
    }

#else
    if (e.type == SDL_EVENT_QUIT) {
      ctx->quit = true;
    }
#endif
    // Button_handleEvent(
    //     &ctx->butt, &e,
    //     &ctx->isButtPressed); // should likely be moved into the game script
  }

  // if (Mix_PlayingMusic() == 0) {
  //   if (ctx->isButtPressed) {
  //     Mix_PlayMusic(ctx->gameMusic, -1);
  //   }
  // } else {
  //   if (!ctx->isButtPressed && (Mix_PausedMusic() == 0)) {
  //     Mix_PauseMusic();
  //   } else if (ctx->isButtPressed && Mix_PausedMusic() == 1) {
  //     Mix_ResumeMusic();
  //   }
  //}

  // ACTUAL GAME STUFF

  // FPS Stuff
  // Uint32 avgFps = ctx->frameCount / (Timer_getTicks(&ctx->fps) / 1000.f);
  // char fpsText[50] = "";
  // snprintf(fpsText, sizeof(fpsText), "fps: %d",
  //  avgFps); // Feeds int into char buffer
  //
  //
  Game_Update(ctx); // calls update in the game.c file

  // START OF RENDERING
  SDL_SetRenderDrawColor(ctx->renderer, 0b00001111, 0b00001111, 0b00001111,
                         0xFF);
  SDL_RenderClear(ctx->renderer);

  // OBJECT RENDERING
  Game_Render(ctx);

  // UI RENDERING
  // if (!Texture_loadFromRenderedText(&ctx->fpsTexture, ctx->renderer,
  // ctx->gFont, fpsText, ctx->fpsCol)) {
  // printf("Couldn't render fps text!!\n");
  // } else {
  // Texture_render(&ctx->fpsTexture, ctx->renderer, NULL, &ctx->fpsLoc, 0.0,
  // NULL, SDL_FLIP_NONE);
  // }
  // Button_render(&ctx->butt, ctx->renderer);

  // printf("%f\n",camera.yPos);   PRINT CAMERA POS

  // RENDER
  SDL_RenderPresent(ctx->renderer);
  ctx->frameCount++;

  // FPS CAP
  // int frameTicks = Timer_getTicks(&ctx->capTimer);
  // if (frameTicks < ctx->ticksPerFrame) {
  //   SDL_Delay(ctx->ticksPerFrame - frameTicks);
  // }
}
/*---------------------------------- END GAME LOOP
 * ----------------------------------*/

bool init(context *ctx) {
  bool success = false;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
  } else {
    if(!SDL_CreateWindowAndRenderer("Game Name", ctx->width, ctx->height, 0, &ctx->window, &ctx->renderer)){
      SDL_Log("Could not make window and renderer: %s", SDL_GetError());
    }
   } //else {
        // int imgFlags = IMG_INIT_PNG;
        // if (!(IMG_Init(imgFlags) & imgFlags)) {
        //   printf("SDL_image could not be initialized! SDL_image Error: %s\n",
        //          IMG_GetError());
        // }

        //else */{
          // Init audio stuff
          /*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("Mix could not init! SDL_Mix Error: %s\n", Mix_GetError());
          } else*/ {
            // Initialize SDL_ttf
            /*if (TTF_Init() == -1) {
              printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
                     TTF_GetError());
            } else */{
              // LOAD MEDIA
              if (!loadMedia(ctx)) {
                printf("Could not load texture image!\n");
              } /*else {
                // CHECK FOR JOYSTICKS AND SET TEXTURE FILTERING

                // Set texture filtering to linear
                // if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                //   printf("Warning: Linear texture filtering not enabled!");
                // }

                // Check for joysticks
                // if (SDL_NumJoysticks() < 1) {
                //   printf("Warning: No joysticks connected!\n");
                // } else {
                //   // Load joystick
                //   ctx->gamePad = SDL_JoystickOpen(0);
                //   if (ctx->gamePad == NULL) {
                //     printf("Warning: Unable to open game controller! SDL "
                //            "Error: %s\n",
                //            SDL_GetError());
                //   }
                }*/
                success = true;
              }
            }

  return success;
}

void quit(context *ctx) {
  printf("Freeing\n");
  Game_Stop(ctx);
  // Texture_free(&ctx->fontTexture);
  // Texture_free(&test);
  // Texture_free(&ctx->fpsTexture);
  // TTF_CloseFont(ctx->gFont);
  // ctx->gFont = NULL;
  // ctx->gamePad = NULL;
  // Mix_FreeChunk(ctx->soundEffect);
  // Mix_FreeMusic(ctx->gameMusic);
  // ctx->soundEffect = NULL;
  // ctx->gameMusic = NULL;
  // Button_free(&ctx->butt);
  // SDL_DestroyRenderer(ctx->renderer);
  // SDL_DestroyWindow(ctx->window);
  // ctx->window = NULL;
  // ctx->renderer = NULL;
  // Mix_Quit();
  // TTF_Quit();
  // IMG_Quit();
  // SDL_Quit();
  printf("Application finished\n");
}

int main(int argc, char *argv[]) {
#ifdef __LINUX__
  printf("Working linux\n");
#endif
#ifdef __APPLE__
  printf("Working apple\n");
#endif
  context ctx; // Defining context
  // CONTEXT STUFF
  ctx.quit = false;
  /* Important stuff */
  ctx.ticksPerFrame = 1000.0f / TARGET_FPS;
  ctx.window = NULL;   // freed
  ctx.renderer = NULL; // freed
  ctx.width = SCREEN_WIDTH;
  ctx.height = SCREEN_HEIGHT;
  /* Textures/Fonts */
  // ctx.gFont = NULL; // freed

  // /* Music/Sounds */
  // ctx.soundEffect = NULL; // freed
  // ctx.gameMusic = NULL;   // freed

  // fps stuff
  // ctx.fpsLoc = (SDL_FRect){SCREEN_WIDTH - 50, 0, 50, 25};
  // ctx.fpsCol = (SDL_Color){200, 200, 200, 255};

  // button
  // ctx.isButtPressed = false;
  // END CONTEXT STUFF

  srand((unsigned int)time(NULL));
  if (!init(&ctx))
    printf("Init not loaded properly!");
  else {
    startGameloop(&ctx);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(gameLoop, &ctx, -1, 1);
#else
    while (!ctx.quit)
      gameLoop(&ctx);
#endif /* ifdef __EMSCRIPTEN__ */
  }
  quit(&ctx);

  return 0;
}
