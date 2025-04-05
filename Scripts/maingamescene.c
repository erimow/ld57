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
  Entity_initPhysics(&player, 0, 0, 32, 32, 32, 32, (SDL_FPoint){0,0}, 1, 1, 1, .5f, 10, 1);
  Texture_init(&tmSpriteSheet);
  Texture_loadFromFile(&tmSpriteSheet, ctx->renderer, "../Art/TileSpritesheet.png");
  Tilemap_init(&tm, &tmSpriteSheet, true, 1, 64, "../level1.txt", "X", 1, "", 0, NULL, 0);
  Camera_init(&cam);
}



static void maingamescene_start(
    void *ct) { //SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS START SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  context *ctx = (context *)ct;
  Camera_setPosition(&cam, 0, 0);
}



static void maingamescene_update(
    context *ctx) { //UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU UPDATE UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
}



static void maingamescene_render(
    SDL_Renderer *renderer) { // RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR RENDER RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderClear(renderer);
    Tilemap_render(&tm, renderer, &cam);
}



static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE  EVENTS EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
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
