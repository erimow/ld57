#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "card.h"

#include <stdbool.h>
#include <stdio.h>

static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 4 - ((float)SCREEN_WIDTH / 4) / 2,
    SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
    SCREEN_WIDTH - (float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
static SDL_FPoint mousePos;
static Card cardsInHand[7];
static Card c;

static void maingamescene_loadAssets(SDL_Renderer *renderer) {
  if (!Texture_loadFromFile(&c.CardBackdrop, renderer, "Art/CardBackdrop.png"))
    printf("Could not load CardBackdrop\n");
}

static void maingamescene_start() {
  c.isSelected = false;
  c.pos = (SDL_FRect){50, 100, 100, 150};
  for (int i = 0; i < 7; i++) {
    cardsInHand[i] = c;
    cardsInHand[i].pos.x += 150 * i;
  }
}
static void maingamescene_update() {
  for (int i = 0; i < 7; i++) {
    Card *a = &cardsInHand[i];
    if (a->isSelected) {
      a->pos.x = mousePos.x - cardsInHand[i].whenSelectedMousePos.x;
      a->pos.y = mousePos.y - cardsInHand[i].whenSelectedMousePos.y;
    }
  }
}
static void maingamescene_render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
  SDL_RenderRect(renderer, &handLocation);
  for (int i = 0; i < 7; i++) {
    Card_Render(&cardsInHand[i], renderer);
  }
}

static void maingamescene_stop() {
  Texture_free(&c.CardBackdrop);
  for (int i = 0; i < 7; i++) {
    Texture_free(&cardsInHand[i].CardBackdrop);
  }
}
static void getMousePos(SDL_Event *e);
static void maingamescene_events(SDL_Event *e) {
  getMousePos(e);
  for (int i = 0; i < 7; i++) {
    Card_HandleEvents(&cardsInHand[i], e, mousePos);
  }
}
static void getMousePos(SDL_Event *e) {
  if (e->type == SDL_EVENT_MOUSE_MOTION) {
    // Get mouse position
    float x, y;
    SDL_GetMouseState(&x, &y);
    mousePos.x = x;
    mousePos.y = y;
  }
}
