#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "card.h"
#include "deck.h"

#include <stdbool.h>
#include <stdio.h>
const static int fontSize = 12;
static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 4 - ((float)SCREEN_WIDTH / 4) / 2,
    SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
    SCREEN_WIDTH - (float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
static SDL_FPoint mousePos;
// static unsigned int curCard = 22;
static unsigned int numCardsToDeal = 7;
static unsigned int numPlayas = 4;
static Deck deck;
static Player *players;
static Button butt; // test

static void maingamescene_loadAssets(
    SDL_Renderer
        *renderer) { //-------------------------------------------ASSET-LOADING
  if (!Texture_loadFromFile(&deck.spriteSheet, renderer,
                            "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n"); // loading in the
                                                // cardspritesheet
  Button_initAndLoad(&butt, renderer, 15, 15, 120, 30,
                     "Art/ButtonBackground.png", "Is this working",
                     (SDL_Color){5, 5, 5, 255});
}

static void
maingamescene_start() { //---------------------------------------------------START
  Deck_init(&deck);
  players = (Player *)malloc(sizeof(Player) * numPlayas);
  Player_InitPlayers(players, numPlayas);
  Deck_deal(&deck, players, numPlayas, numCardsToDeal);
  // printf("player 0 cards in hand -> %d\n", players[0].numCardsInHand);
}
static void
maingamescene_update() { //--------------------------------------------------UPDATE
  for (int i = 0; i < players[0].numCardsInHand; i++) {
    Card *a = players[0].hand[i];
    if (a->isSelected) {
      a->pos.x = mousePos.x - a->whenSelectedMousePos.x;
      a->pos.y = mousePos.y - a->whenSelectedMousePos.y;
    }
  }
}
static void maingamescene_render(
    SDL_Renderer *renderer) { // -------------------------------------- RENDER
  SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
  SDL_RenderRect(renderer, &handLocation);
  // for (int i = 0; i<numPlayas; i++){
  //   Player_
  // }
  Player_RenderHand(&players[0], renderer, &handLocation);

  // UI
  Button_render(&butt, renderer);
}

static void
maingamescene_stop() { // --------------------------------------------STOP
  Button_free(&butt);
  Texture_free(&deck.spriteSheet);
  free(players);
}

static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // -------------------------------------------------  EVENTS
  getMousePos(e);
  for (int i = 0; i < players[0].numCardsInHand; i++) {
    Card_HandleEvents(players[0].hand[i], e, mousePos);
  }

  // UI
  Button_handleEvent(&butt, e);
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
