#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "card.h"
#include "deck.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
typedef enum Phase { deal, play, scoring } Phase;
const static int fontSize = 34;
const static Uint8 cardGap = 15;
static SDL_FRect handLocation = {
    (float)SCREEN_WIDTH / 8, SCREEN_HEIGHT - (float)SCREEN_HEIGHT / 4,
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
static Button playbutt; // test
static Button predictionButtons[9];
static Texture roundText;

static void maingamescene_loadAssets(
    context *ctx) { //-------------------------------------------ASSET-LOADING

  if (!Texture_loadFromFile(&deck.spriteSheet, ctx->renderer,
                            "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n"); // loading in the
                                                // cardspritesheet
  Button_initAndLoad(&playbutt, ctx->renderer, 15,
                     ((float)SCREEN_WIDTH / 2) - 15, 120, 50,
                     "Art/ButtonBackground.png", ctx->gFont, "Play", 4,
                     (SDL_Color){5, 5, 5, 255});
  for (int i = 0; i < 9; i++) {
    char text[2];
    snprintf(text, 2, "%d", i);
    Button_initAndLoad(&predictionButtons[i], ctx->renderer,
                       handLocation.x + handLocation.w + 15 +
                           ((i % 2) * (((float)SCREEN_WIDTH / 16) - 7.5f)),
                       (float)SCREEN_HEIGHT / 3 +
                           ((i / 2) * (((float)SCREEN_HEIGHT / 16) + 7.5f)),
                       ((float)SCREEN_WIDTH / 16) - 20,
                       ((float)SCREEN_HEIGHT / 16) - 5,
                       "Art/ButtonBackground.png", ctx->gFont, text, 1,
                       (SDL_Color){5, 5, 5, 255});
  }
  Texture_init_andLoadFromRenderedText(
      &roundText, ctx->renderer, ctx->gFont, (SDL_FRect){15, 15, 250, 60},
      "Round of 8", 10, (SDL_Color){255, 255, 255, 255});
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
static void maingamescene_update(
    context *ctx) { //--------------------------------------------------UPDATE
  switch (currentPhase) {
  case deal:
    Deck_scramble(&deck);
    Deck_deal(&deck, players, numPlayas, --round);
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

  // UI
  switch (currentPhase) {
  case deal:
    break;
  case play:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    Player_RenderHand(&players[0], renderer, &handLocation, &playLocation);
    Button_render(&playbutt, renderer);
    for (int i = 0; i < 9; i++) {
      Button_render(&predictionButtons[i], renderer);
    }
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    break;
  case scoring:
    break;
  }
}

static void
maingamescene_stop() { // --------------------------------------------STOP
  Button_free(&playbutt);
  for (int i = 0; i < 9; i++) {
    Button_free(&predictionButtons[i]);
  }
  Texture_free(&roundText);
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
  Button_handleEvent(&playbutt, e);
  for (int i = 0; i < 9; i++) {
    Button_handleEvent(&predictionButtons[i], e);
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
