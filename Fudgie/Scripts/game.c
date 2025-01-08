#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "card.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum Scenes { MAINMENU, GAME } Scenes;
static Scenes currentScene;
static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 4 - ((float)SCREEN_WIDTH / 4) / 2,
    SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
    SCREEN_WIDTH - (float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
static SDL_FPoint mousePos;
static Card cardsInHand[7];
static Card c;

static void loadAssets(context *ctx) {
  if (!Texture_loadFromFile(&c.CardBackdrop, ctx->renderer,
                            "Art/CardBackdrop.png"))
    printf("Could not load CardBackdrop\n");
}

static void Game_Start(context *ctx) {
  loadAssets(ctx);
  currentScene = GAME;
  c.isSelected = false;
  c.pos = (SDL_FRect){50, 100, 100, 150};
  for (int i = 0; i < 7; i++) {
    cardsInHand[i] = c;
    cardsInHand[i].pos.x += 150 * i;
  }
}

static void Game_Update(context *ctx) {
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    // call games function
    break;
  }
  for (int i = 0; i < 7; i++) {
    Card *a = &cardsInHand[i];
    if (a->isSelected) {
      a->pos.x = mousePos.x - cardsInHand[i].whenSelectedMousePos.x;
      a->pos.y = mousePos.y - cardsInHand[i].whenSelectedMousePos.y;
    }
  }
}

static void Game_Render(context *ctx) {
  SDL_SetRenderDrawColor(ctx->renderer, 255, 100, 0, 255);
  SDL_RenderDrawRectF(ctx->renderer, &handLocation);
  for (int i = 0; i < 7; i++) {
    Card_Render(&cardsInHand[i], ctx->renderer);
  }
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    // call games function
    break;
  }
}

static void Game_Stop(context *ctx) {
  printf("stopping game\n");
  Texture_free(&c.CardBackdrop);
  for (int i = 0; i < 7; i++) {
    Texture_free(&cardsInHand[i].CardBackdrop);
  }
  printf("game assets stopped\n");
}
static void getMousePos(SDL_Event *e);
static void Game_Events(context *ctx, SDL_Event *e) {
  getMousePos(e);
  for (int i = 0; i < 7; i++) {
    Card_HandleEvents(&cardsInHand[i], e, mousePos);
  }
  switch (currentScene) {
  case MAINMENU:
    break;
  case GAME:
    // call games function
    break;
  }
}

static void getMousePos(SDL_Event *e) {
  if (e->type == SDL_MOUSEMOTION) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    mousePos.x = x;
    mousePos.y = y;
  }
}
