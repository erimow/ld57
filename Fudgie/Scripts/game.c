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
//enum storing scene names in context.h

static void loadAssets(context *ctx) {
  //scenemanager stuff
  SceneManager_init(&ctx->sm, 2);//2 scenes to init with
  SceneManager_addScene(&ctx->sm, MAINMENU, mainmenuscene_loadAssets ,mainmenuscene_start, mainmenuscene_stop);
  SceneManager_addScene(&ctx->sm, GAME, maingamescene_loadAssets ,maingamescene_start, maingamescene_stop);

  //game stuff
  // Functions below call the loadAssets functions and tell the SceneManager they are loaded.... That is really the only difference
  SceneManager_loadScene(&ctx->sm, MAINMENU, ctx);// mainmenuscene_loadAssets(ctx);
  SceneManager_loadScene(&ctx->sm, GAME, ctx);// maingamescene_loadAssets(ctx);
}

static void Game_Start(context *ctx) {
  // SceneManager_init(&sceneManager);//initialize scenemanager
  loadAssets(ctx);
  SceneManager_switchScene(&ctx->sm, MAINMENU, ctx); //Also loads scene if not previously loaded
  // mainmenuscene_start();
  // maingamescene_start();
}

static void Game_Update(context *ctx) {
  switch (ctx->sm.currentScene) {
  case MAINMENU:
    mainmenuscene_update(ctx);
    break;
  case GAME:
    maingamescene_update(ctx);
    break;
  }
}

static void Game_Render(context *ctx) {
  switch (ctx->sm.currentScene) {
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
  SceneManager_deinit(&ctx->sm);

  mainmenuscene_stop();
  maingamescene_stop();
}
static void Game_Events(context *ctx,
                        SDL_Event *e) { // events are called before update
  switch (ctx->sm.currentScene) {
  case MAINMENU:
    mainmenuscene_handleEvents(e);
    break;
  case GAME:
    maingamescene_events(e);
    break;
  }
}
