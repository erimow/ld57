#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/Tilemap.h"
#include "../Engine/Entity.h"
#include "../Engine/BackgroundEntity.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ==============================================================================================================================
// ==============================================================================================================================

static Entity player;
static Tilemap tm;
static Texture tmSpriteSheet;
static Camera cam;
// ==============================================================================================================================


static void maingamescene_loadAssets(
    void *ct) { //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ASSET-LOADING AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  context *ctx = (context *)ct;
  Entity_initPhysics(&player, 0, 0, 64, 64, 64, 64, (SDL_FPoint){0,0}, 2, 1.5, .4f, .8f, 30, 1);
  if(!Entity_setTexture(&player, ctx->renderer, "Art/PlayerSpritesheet.png")){SDL_Log("couldnt load play texture\n");}
  Texture_init(&tmSpriteSheet);
  if(!Texture_loadFromFile(&tmSpriteSheet, ctx->renderer, "Art/TileSpritesheet.png")){
    SDL_Log("Unable to load tilespritesheet!\n");
  }
  Tilemap_init(&tm, &tmSpriteSheet, true, 1, 64, "level1.txt", "X", 1, "", 0, NULL, 0);
  Camera_init(&cam);
}



static void maingamescene_start(
    void *ct) { //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS START SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  context *ctx = (context *)ct;
}



static void maingamescene_update(
    context *ctx) { //UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU UPDATE UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
      Uint8 colliderAmount = 0;
      SDL_FRect **colliderAroundPlayer = Tilemap_getCollidersAroundEntity(&tm, &player, &colliderAmount);
      Entity_move(&player, colliderAroundPlayer, colliderAmount);
      Camera_setPosition(&cam, player.xPos+(player.collider.w/2), player.yPos+(player.collider.h/2));
      Camera_setBounds(&cam, (SDL_FRect){0,0,Tilemap_getMapWidthPixels(&tm),Tilemap_getMapHeightPixels(&tm)});
}



static void maingamescene_render(
    SDL_Renderer *renderer) { // RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR RENDER RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    SDL_SetRenderDrawColor(renderer, 180, 59, 59, 255);
    SDL_RenderClear(renderer);
    Tilemap_render(&tm, renderer, &cam);
    Entity_render(&player, renderer, &(SDL_FRect){0,0,32,32}, 0, NULL, SDL_FLIP_NONE, &cam, 1);
}



static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE  EVENTS EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
      Entity_handleEvent(&player, e);
}

static void
maingamescene_stop() { // SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS STOP SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  Texture_free(&tmSpriteSheet);
  Tilemap_free(&tm);
  Entity_free(&player, false);
  Camera_free(&cam);
}

// static void getMousePos(SDL_Event *e) {
//   if (e->type == SDL_EVENT_MOUSE_MOTION) {
//     // Get mouse position
//     float x, y;
//     SDL_GetMouseState(&x, &y);
//     mousePos.x = x;
//     mousePos.y = y;
//   }
// }
