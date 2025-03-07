#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "../Engine/scenemanager.h"
#include "./maingamescene.c"
#include "./mainmenu.c"
#include "card.h"

#include <stdbool.h>
#include <stdio.h>

// static SceneManager sceneManager;

static void loadAssets(context *ctx) {
  mainmenuscene_loadAssets(ctx);
  maingamescene_loadAssets(ctx);
}

static void Game_Start(context *ctx) {
  // SceneManager_init(&sceneManager);//initialize scenemanager
  loadAssets(ctx);
  ctx->currentScene = MAINMENU;
  mainmenuscene_start();
  maingamescene_start();
}

static void Game_Update(context *ctx) {
  switch (ctx->currentScene) {
  case MAINMENU:
    mainmenuscene_update(ctx);
    break;
  case GAME:
    maingamescene_update(ctx);
    break;
  }
}

static void Game_Render(context *ctx) {
  switch (ctx->currentScene) {
  case MAINMENU:
    mainmenuscene_render(ctx->renderer);
    break;
  case GAME:
    maingamescene_render(ctx->renderer);
    break;
  }
}

static void Game_Stop(context *ctx) {
  printf("Stopping game\n");
  mainmenuscene_stop();
  maingamescene_stop();
}
static void Game_Events(context *ctx,
                        SDL_Event *e) { // events are called before update
  switch (ctx->currentScene) {
  case MAINMENU:
    mainmenuscene_handleEvents(e);
    break;
  case GAME:
    maingamescene_events(e);
    break;
  }
}
