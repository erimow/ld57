#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "card.h"
#include "deck.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
typedef enum Phase { deal, play, predict, scoring } Phase;
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
static unsigned int round = 8;
static Uint8 playerCount;
static Phase currentPhase;
static Deck deck;
static Player *players = NULL;
static Player *playerPlaying = NULL;
static Texture *playerText = NULL;
static Button playbutt; // test
static Button predictionButtons[9];
static Texture roundText;
// static Texture currentPredictionText;
static Texture phaseOrTurnText;

static void maingamescene_loadAssets(
    void *ct) { //-------------------------------------------ASSET-LOADING
  context *ctx = (context*)ct;
  if (!Texture_loadFromFile(&deck.spriteSheet, ctx->renderer,
                            "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n"); // loading in the
                                                // cardspritesheet
  Button_initAndLoad(&playbutt, ctx->renderer, 15,
                     ((float)SCREEN_WIDTH / 2) - 15, 120, 50,
                     "Art/ButtonBackground.png", ctx->gFont, "Play", 4,
                     (SDL_Color){5, 5, 5, 255});
  for (int i = 0; i < round+1; i++) {
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
  // Texture_init_andLoadFromRenderedText(
  //     &currentPredictionText, ctx->renderer, ctx->gFont, (SDL_FRect){15, 75, 200, 30},
  //     "Current prediction: -1", 22, (SDL_Color){255, 255, 255, 255});
  Texture_init_andLoadFromRenderedText(
      &phaseOrTurnText, ctx->renderer, ctx->gFont, (SDL_FRect){((float)SCREEN_WIDTH/2)-125, 15, 250, 60},
      "Prediction Phase", 16, (SDL_Color){255, 255, 255, 255});
}

static void
maingamescene_start(void *ct) { //---------------------------------------------------START
  context *ctx = (context*)ct;
  playerCount = ctx->numPlayas;

  Deck_init(&deck);
  Deck_scramble(&deck);
  if (players!=NULL){
    free(players);
  }
  players = (Player *)malloc(sizeof(Player) * ctx->numPlayas);
  Player_InitPlayers(players, ctx->numPlayas);
  playerText = (Texture *)malloc(sizeof(Texture)* ctx->numPlayas);
  for (int i = 0; i<ctx->numPlayas; i++){
    char t[50];
    snprintf(t, 50, "Player %d: -1",i+1);
    Texture_init_andLoadFromRenderedText(&playerText[i], ctx->renderer, ctx->gFont, (SDL_FRect){15,75+(i*30),200,30}, t, 12, (SDL_Color){255,255,255,255});
  }
  Deck_deal(&deck, players, ctx->numPlayas, round);
  currentPhase = predict;
}
static void maingamescene_update(
    context *ctx) { //--------------------------------------------------UPDATE
  switch (currentPhase) {
  case deal:
    Deck_scramble(&deck);
    Deck_deal(&deck, players, ctx->numPlayas, --round);
    currentPhase = play;
    break;
  case predict:
  for (int i = 0; i<round+1;i++){
    if (predictionButtons[i].isButtPressed){
      players[0].currentPrediction=i;
      predictionButtons[i].isButtPressed=false;
      char t[22];
      snprintf(t, 22, "Player 1: %d", i);
  Texture_init_andLoadFromRenderedText(
      &playerText[0], ctx->renderer, ctx->gFont, (SDL_FRect){15, 75, 200, 30},
      t, 11, (SDL_Color){255, 255, 255, 255});
      currentPhase=play;
  Texture_init_andLoadFromRenderedText(
      &phaseOrTurnText, ctx->renderer, ctx->gFont, (SDL_FRect){((float)SCREEN_WIDTH/2)-125, 15, 250, 60},
      "Player 1's Turn", 15, (SDL_Color){255, 255, 255, 255});
      currentPhase=play;
    }
  }
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
  case predict:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    Player_RenderHand(&players[0], renderer, &handLocation, &playLocation);

    Texture_render(&phaseOrTurnText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
     for (int i = 0; i < round+1; i++) {
      Button_render(&predictionButtons[i], renderer);
    }
    for (int i = 0; i<playerCount; i++){
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  case play:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    Player_RenderHand(&players[0], renderer, &handLocation, &playLocation);
    if (cardSelected!=NULL)
      Button_render(&playbutt, renderer);

    Texture_render(&phaseOrTurnText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    // Texture_render(&currentPredictionText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    for (int i = 0; i<playerCount; i++){
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  case scoring:
    break;
  }
}

static void
maingamescene_stop() { // --------------------------------------------STOP
  Button_free(&playbutt);
  for (int i = 0; i < round+1; i++) {
    Button_free(&predictionButtons[i]);
  }
  for (int i = 0; i<playerCount; i++){
    Texture_free(&playerText[i]);
  }
  free(playerText);
  Texture_free(&phaseOrTurnText);
  // Texture_free(&currentPredictionText);
  Texture_free(&roundText);
  Texture_free(&deck.spriteSheet);
  free(players);
}

static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // -------------------------------------------------  EVENTS
  getMousePos(e);
  switch (currentPhase){
    case deal:
      break;
    case predict:
  for (int i = 0; i < round+1; i++) {
    Button_handleEvent(&predictionButtons[i], e);
  }
      break;
    case play:
  for (int i = players[0].numCardsInHand - 1; i >= 0; i--) {
    Card_HandleEvents(players[0].hand[i], e, mousePos, &playLocation,
                      &cardBeingHeld, &cardSelected);
  }
    if (cardSelected != NULL)
      Button_handleEvent(&playbutt, e);
  break;

    case scoring:
      break;
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
