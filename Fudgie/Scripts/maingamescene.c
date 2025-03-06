#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include "card.h"
#include "deck.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
typedef enum Phase { deal, play, scoring } Phase;
const static int fontSize = 34;
const static Uint8 cardGap = 15;
static TTF_Font *gFont;
static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 4 - ((float)SCREEN_WIDTH / 4) / 2,
    SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
    SCREEN_WIDTH - (float)SCREEN_WIDTH / 4, (float)SCREEN_HEIGHT / 4};
static SDL_FRect playLocation = {
    ((float)SCREEN_WIDTH / 2) -
        (float)((CARDPXWIDTH * 4) + (float)cardGap * 3) / 2,
    ((float)SCREEN_HEIGHT / 2) - (float)CARDPXHEIGHT / 2,
    (float)(CARDPXWIDTH * 4) + (float)cardGap * 3, (float)CARDPXHEIGHT};
static SDL_FPoint mousePos;
    //----------------------------------------------------------------------
static Card *cardBeingHeld = NULL;
static Card *cardSelected = NULL;
static unsigned int numPlayas = 4;
static unsigned int round = 8;
static Phase currentPhase;
static Deck deck;
static Player *players;
static Button butt; // test

static void maingamescene_loadAssets(
    SDL_Renderer
        *renderer) { //-------------------------------------------ASSET-LOADING
  gFont = TTF_OpenFont("Fonts/tuffy_regular.ttf",
                            56); // Location and font size;
  if(gFont == NULL){
    printf("Could not load font!\n");
  }
  if (!Texture_loadFromFile(&deck.spriteSheet, renderer,
                            "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n"); // loading in the
                                                // cardspritesheet
  Button_initAndLoad(&butt, renderer, 15, ((float)SCREEN_WIDTH / 2) - 15, 120,
                     50, "Art/ButtonBackground.png", gFont, "Play",
                     (SDL_Color){5, 5, 5, 255});
}

static void
maingamescene_start() { //---------------------------------------------------START
  Deck_init(&deck);
  Deck_scramble(&deck);
  players = (Player *)malloc(sizeof(Player) * numPlayas);
  Player_InitPlayers(players, numPlayas);
  Deck_deal(&deck, players, numPlayas, round);
  currentPhase = play;
}
static void
maingamescene_update() { //--------------------------------------------------UPDATE
  switch (currentPhase) {
  case deal:
    // Deck_scramble(&deck);
    // Deck_deal(&deck, players, numPlayas, --round);
    currentPhase = play;
    break;
  case play:
    for (int i = 0; i < players[0].numCardsInHand; i++) {
      Card *a = players[0].hand[i];
      if (a->isHeld) {
        a->pos.x = mousePos.x - a->whenHeldMousePos.x;
        a->pos.y = mousePos.y - a->whenHeldMousePos.y;
        if (players[0].numCardsInHand > 1 &&
            (a->pos.y + ((float)CARDPXHEIGHT / 2)) > handLocation.y) {
          if (i != 0) {
            if (a->pos.x + ((float)CARDPXWIDTH / 2) <
                players[0].hand[i - 1]->pos.x + ((float)CARDPXWIDTH / 2)) {
              players[0].hand[i] = players[0].hand[i - 1];
              players[0].hand[i - 1] = a;
            }
          }
          if (i != players[0].numCardsInHand - 1) {
            if (a->pos.x + ((float)CARDPXWIDTH / 2) >
                players[0].hand[i + 1]->pos.x + ((float)CARDPXWIDTH / 2)) {
              players[0].hand[i] = players[0].hand[i + 1];
              players[0].hand[i + 1] = a;
            }
          }
        }
      }
    }
    break;
  case scoring:

    break;
  }
}
static void maingamescene_render(
    SDL_Renderer *renderer) { // -------------------------------------- RENDER
  SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
  SDL_RenderRect(renderer, &handLocation);
  SDL_RenderRect(renderer, &playLocation);

  // UI
  switch (currentPhase) {
  case deal:
    break;
  case play:
    Player_RenderHand(&players[0], renderer, &handLocation, &playLocation);
    Button_render(&butt, renderer);
    break;
  case scoring:
    break;
  }
}

static void
maingamescene_stop() { // --------------------------------------------STOP
  TTF_CloseFont(gFont);
  Button_free(&butt);
  Texture_free(&deck.spriteSheet);
  free(players);
}

static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // -------------------------------------------------  EVENTS
  getMousePos(e);
  for (int i = players[0].numCardsInHand - 1; i >= 0; i--) {
    Card_HandleEvents(players[0].hand[i], e, mousePos, &playLocation,
                      &cardBeingHeld, &cardSelected);
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
