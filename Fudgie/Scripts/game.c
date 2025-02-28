#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "./maingamescene.c"
#include "card.h"

#include <stdbool.h>
#include <stdio.h>

typedef enum Scenes { MAINMENU, GAME } Scenes;
static Scenes currentScene;

static void loadAssets(context *ctx) {
  maingamescene_loadAssets(ctx->renderer);
}

static void Game_Start(context *ctx) {
  loadAssets(ctx);
  currentScene = GAME;
  maingamescene_start();
}

static void Game_Update(context *ctx) {
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    maingamescene_update();
    break;
  }
}

static void Game_Render(context *ctx) {
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    maingamescene_render(ctx->renderer);
    break;
  }
}

static void Game_Stop(context *ctx) {
  printf("Stopping game\n");
  maingamescene_stop();
}
static void Game_Events(context *ctx,
                        SDL_Event *e) { // events are called before update
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    maingamescene_events(e);
    break;
  }
}
