#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "card.h"
#include "deck.h"

#include <stdbool.h>
#include <stdio.h>

static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 4 - ((float)SCREEN_WIDTH / 4) / 2,
    SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
    SCREEN_WIDTH - (float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
static SDL_FPoint mousePos;
static Deck deck;

static void maingamescene_loadAssets(SDL_Renderer *renderer) {
  if (!Texture_loadFromFile(&deck.spriteSheet, renderer, "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n");  //loading in the cardspritesheet

}
static unsigned int curCard = 22;
static void maingamescene_start() {
  Deck_init(&deck);
  deck.cards[curCard].pos = (SDL_FRect){50, 150, 125, 175};
}
static void maingamescene_update() {
  // for (int i = 0; i < 7; i++) {
    Card *a = &deck.cards[curCard];
    if (a->isSelected) {
      a->pos.x = mousePos.x - a->whenSelectedMousePos.x;
      a->pos.y = mousePos.y - a->whenSelectedMousePos.y;
    }
  // }
}
static void maingamescene_render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
  SDL_RenderRect(renderer, &handLocation);
  // for (int i = 0; i < 7; i++) {
  //   Card_Render(&cardsInHand[i], renderer);
  // }
  Card_Render(&deck.cards[curCard], renderer);
}

static void maingamescene_stop() {
  Texture_free(&deck.spriteSheet);
}
static void getMousePos(SDL_Event *e);
static void maingamescene_events(SDL_Event *e) {
  getMousePos(e);
  // for (int i = 0; i < 7; i++) {
  //   Card_HandleEvents(&cardsInHand[i], e, mousePos);
  // }
  Card_HandleEvents(&deck.cards[curCard], e, mousePos);
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
