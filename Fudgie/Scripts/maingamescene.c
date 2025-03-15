#include "../Engine/Button.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "card.h"
#include "deck.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CPU_DELAY 15000
#define PREDICTBUTTONAMOUNT 11
#define TOTALROUNDS 3

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
static Uint8 playerCount;
static Phase currentPhase; // phase of game
static Deck deck;
static Player *players = NULL;

static Texture *playerText = NULL; // text displaying player predictions
static Texture *playerPointText = NULL; // text displaying player points
static Button playbutt; // play button to be displayed for userPlaying
static Button predictionButtons[PREDICTBUTTONAMOUNT]; // probably need to switch to a pointer for
                                    // adjustability
static Texture roundText;           // text in corner displaying current round
// static Texture currentPredictionText;
static Texture phaseOrTurnText; // Text at top of screen
//-------------------------------------------------------------------
static Card *cardBeingHeld = NULL; // user playing stuff
static Card **cardSelected = NULL; // user playing stuff
static Uint8 selectedCount = 0;
static Uint8 round = TOTALROUNDS;       // round, cards dealt
static bool roundsCountingUp = false;
static Uint8 userPlaying = 0; // the player the user is playing
static Uint8 playerPlaying = 0; // keep track of player whos turn it is
static Uint8 playerStartingRound =
    0; // keep track of player who started round or other non prediction
static Uint8 playerStartingPrediction =
    0; // keep track of player who initiated prediction
    static Uint8 combinedRoundPredictions= 0;
static char currentHandsSuit = '\0';

static void maingamescene_loadAssets(
    void *ct) { //-------------------------------------------ASSET-LOADING
  context *ctx = (context *)ct;
  if (!Texture_loadFromFile(&deck.spriteSheet, ctx->renderer,
                            "Art/CardSpritesheet.png"))
    printf("Could not load CardSpritesheet\n"); // loading in the
                                                // cardspritesheet
  Button_initAndLoad(&playbutt, ctx->renderer, 15,
                     ((float)SCREEN_WIDTH / 2) - 15, 120, 50,
                     "Art/ButtonBackground.png", ctx->gFont, "Play", 4,
                     (SDL_Color){5, 5, 5, 255});
  for (int i = 0; i < round + 1; i++) {
    char text[3];
    snprintf(text, 3, "%d", i);
    Button_initAndLoad(&predictionButtons[i], ctx->renderer,
                       handLocation.x + handLocation.w + 15 +
                           ((i % 2) * (((float)SCREEN_WIDTH / 16) - 7.5f)),
                       (float)SCREEN_HEIGHT / 3 +
                           ((i / 2) * (((float)SCREEN_HEIGHT / 16) + 7.5f)),
                       ((float)SCREEN_WIDTH / 16) - 20,
                       ((float)SCREEN_HEIGHT / 16) - 5,
                       "Art/ButtonBackground.png", ctx->gFont, text, 1+i/10,
                       (SDL_Color){5, 5, 5, 255});
  }
  char t[12];
  snprintf(t, 12, "Round of %d", round);
  Texture_init_andLoadFromRenderedText(
      &roundText, ctx->renderer, ctx->gFont, (SDL_FRect){15, 15, 250, 60},
      t, 10+(round/10), (SDL_Color){255, 255, 255, 255});
  // Texture_init_andLoadFromRenderedText(
  //     &currentPredictionText, ctx->renderer, ctx->gFont, (SDL_FRect){15, 75,
  //     200, 30}, "Current prediction: -1", 22, (SDL_Color){255, 255, 255,
  //     255});
  Texture_init_andLoadFromRenderedText(
      &phaseOrTurnText, ctx->renderer, ctx->gFont,
      (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
      "Prediction Phase", 16, (SDL_Color){255, 255, 255, 255});
}

static void maingamescene_start(
    void *ct) { //---------------------------------------------------START
  context *ctx = (context *)ct;
  playerCount = ctx->numPlayas;
  playbutt.isButtPressed = false;
  Deck_init(&deck);
  Deck_scramble(&deck);
  if (players != NULL) {
    free(players);
  }
  // mallocs
  players = (Player *)malloc(sizeof(Player) * ctx->numPlayas);
  Player_InitPlayers(players, ctx->numPlayas);
  playerText = (Texture *)malloc(sizeof(Texture) * ctx->numPlayas);
  playerPointText = (Texture *)malloc(sizeof(Texture) * ctx->numPlayas);
  cardSelected = (Card **)malloc(sizeof(Card *) * ctx->numPlayas);
  playerPlaying = playerStartingPrediction;
  for (int i = 0; i < ctx->numPlayas; i++) {
    cardSelected[i] = NULL;
    char t[50];
    snprintf(t, 50, "Player %d: -1", i);
    if (playerPlaying != i)
      Texture_init_andLoadFromRenderedText(
          &playerText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (i * 30), 200, 30}, t, 11,
          (SDL_Color){255, 255, 255, 175});
    else {
      Texture_init_andLoadFromRenderedText(
          &playerText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (i * 30), 230, 35}, t, 11,
          (SDL_Color){255, 255, 255, 255});
    }
    snprintf(t, 50, "Player %d: 0", i);
      Texture_init_andLoadFromRenderedText(
          &playerPointText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){(SCREEN_WIDTH-170)-15, 15 + (i * 20), 170, 20}, t, 11,
          (SDL_Color){255, 200, 200, 255});
  }
  Deck_deal(&deck, players, ctx->numPlayas, round);
  currentPhase = predict;
}
static void maingamescene_update(
    context *ctx) { //--------------------------------------------------UPDATE
  switch (currentPhase) {
  case deal:
    Deck_scramble(&deck);
    deck.cardsRemainingInDeck=52;
    if (!roundsCountingUp){
      round--;
    }
    else{
      round++;
    }
    if (round==0){
      round = 2;
      roundsCountingUp = true;
    }
    if(round==TOTALROUNDS+1&&roundsCountingUp){
      printf("GAME DONE\n");
    }
    Deck_deal(&deck, players, ctx->numPlayas, round);
    char j[11];
    snprintf(j, 11, "Round of %d", round);
    Texture_init_andLoadFromRenderedText(&roundText, ctx->renderer, ctx->gFont,
                                         (SDL_FRect){15, 15, 250, 60}, j, 10,
                                         (SDL_Color){255, 255, 255, 255});
    currentPhase = predict;
    Texture_init_andLoadFromRenderedText(
        &phaseOrTurnText, ctx->renderer, ctx->gFont,
        (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
        "Predict Phase", 13, (SDL_Color){255, 255, 255, 255});
    playerPlaying = playerStartingPrediction;
  for (int i = 0; i < ctx->numPlayas; i++) {
    cardSelected[i] = NULL;
    char t[50];
    snprintf(t, 50, "Player %d: -1", i);
    if (playerPlaying != i)
      Texture_init_andLoadFromRenderedText(
          &playerText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (i * 30), 200, 30}, t, 11,
          (SDL_Color){255, 255, 255, 175});
    else {
      Texture_init_andLoadFromRenderedText(
          &playerText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (i * 30), 230, 35}, t, 11,
          (SDL_Color){255, 255, 255, 255});
    }
  }
    combinedRoundPredictions = 0;
    break;
  case predict: // --------------------- UPDATE PREDICT-----------------------
    Player_UpdateHand(&players[userPlaying], &mousePos, &handLocation); //ALLOW USER TO ADJUST THEIR HAND DURING PREDICT PHASE, BUT PREVENT THEM FROM PUTTING CARDS IN THE PLAY AREA
    if (cardSelected[userPlaying]!=NULL){
      cardSelected[userPlaying]->isSelected = false;
      cardSelected[userPlaying]=NULL;
    }

    if (playerPlaying == userPlaying) {
      for (int i = 0; i < round + 1; i++) {
        if (predictionButtons[i].isButtPressed) {
          players[userPlaying].currentPrediction = i;
          combinedRoundPredictions+=i;
          predictionButtons[i].isButtPressed = false;
          char t[22];
          snprintf(t, 22, "Player %d: %d", userPlaying, i);
          Texture_init_andLoadFromRenderedText(
              &playerText[userPlaying], ctx->renderer, ctx->gFont,
              (SDL_FRect){15, 75 + (playerPlaying * 30), 200, 30}, t, 11+(players[playerPlaying].currentPrediction/10),
              (SDL_Color){255, 255, 255, 175});
          // Texture_init_andLoadFromRenderedText(
          // &phaseOrTurnText, ctx->renderer, ctx->gFont,
          // (SDL_FRect){((float)SCREEN_WIDTH/2)-125, 15, 250, 60}, "Player 1's
          // Turn", 15, (SDL_Color){255, 255, 255, 255});
          playerPlaying =
              (playerPlaying + 1 == playerCount) ? 0 : playerPlaying + 1;
          if (playerPlaying == playerStartingPrediction) {

            currentPhase = play;
            Texture_init_andLoadFromRenderedText(
                &phaseOrTurnText, ctx->renderer, ctx->gFont,
                (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
                "Play Phase", 10+(players[playerPlaying].currentPrediction/10), (SDL_Color){255, 255, 255, 255});
            Uint8 highestPredictionByPlayer = playerStartingPrediction;
            for (int i = playerStartingPrediction + 1;
                 i < playerStartingPrediction + playerCount; i++) {
              if (players[i % playerCount].currentPrediction >
                  players[highestPredictionByPlayer].currentPrediction) {
                highestPredictionByPlayer = i % playerCount;
              }
            }
            playerStartingPrediction =
                (playerStartingPrediction + 1) % playerCount;
            playerPlaying = highestPredictionByPlayer;
            playerStartingRound = playerPlaying;
          }
          snprintf(t, 22, "Player %d: %d", playerPlaying,
                   players[playerPlaying].currentPrediction);
          Texture_init_andLoadFromRenderedText(
              &playerText[playerPlaying], ctx->renderer, ctx->gFont,
              (SDL_FRect){15, 75 + (playerPlaying * 30), 230, 35}, t, 11+(players[playerPlaying].currentPrediction/10),
              (SDL_Color){255, 255, 255, 255});

        }
      }
    } else { //CPU PREDICT PHASE
      if (ctx->frameCount % CPU_DELAY == 0) {
        char t[40];
        players[playerPlaying].currentPrediction =
            rand() % (round + 1); // makes random prediction
        if ((playerPlaying+1)%playerCount == playerStartingPrediction){
         while ( players[playerPlaying].currentPrediction + combinedRoundPredictions== round){
          players[playerPlaying].currentPrediction =
            rand() % (round + 1); // makes random prediction
        }
        }
        if (round == 1 && players[playerPlaying].currentPrediction!=1)
          players[playerPlaying].currentPrediction=1;//SET PREDICTION TO 1 WHEN ROUND IS 1

        combinedRoundPredictions+=players[playerPlaying].currentPrediction;
        snprintf(t, 40, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
        Texture_init_andLoadFromRenderedText(
            &playerText[playerPlaying], ctx->renderer, ctx->gFont,
            (SDL_FRect){15, 75 + (playerPlaying * 30), 200, 30}, t, 11+(players[playerPlaying].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
            (SDL_Color){255, 255, 255, 175});
        playerPlaying =
            (playerPlaying + 1 == playerCount) ? 0 : playerPlaying + 1;
        if (playerPlaying == playerStartingPrediction) {
          Uint8 highestPredictionByPlayer = 0;
          for (int i = playerStartingPrediction + 1;
               i < playerStartingPrediction + playerCount; i++) {
            if (players[i % playerCount].currentPrediction >
                players[highestPredictionByPlayer].currentPrediction) {
              highestPredictionByPlayer = i % playerCount;
            }
          }
          playerStartingPrediction =
              (playerStartingPrediction + 1) % playerCount;
          playerPlaying = highestPredictionByPlayer;
          playerStartingRound = playerPlaying;

          currentPhase = play;
          Texture_init_andLoadFromRenderedText(
              &phaseOrTurnText, ctx->renderer, ctx->gFont,
              (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
              "Play Phase", 10, (SDL_Color){255, 255, 255, 255});
        }
        snprintf(t, 22, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
        Texture_init_andLoadFromRenderedText(
            &playerText[playerPlaying], ctx->renderer, ctx->gFont,
            (SDL_FRect){15, 75 + (playerPlaying * 30), 230, 35}, t, 11+(players[playerPlaying].currentPrediction/10),
            (SDL_Color){255, 255, 255, 255});
      }
    }
    break;
  case play:  //-------------------------UPDATE PLAY ------------------------
    if (selectedCount == playerCount &&
        playbutt.isButtPressed) { // breaks out and switches to scoring phase if
                                  // in render,
                                  // selectedCount counts to playerCount
      if (ctx->frameCount % CPU_DELAY == 0) {
      currentHandsSuit = cardSelected[playerStartingRound]->suit;
          int8_t winningHand = playerStartingRound;
          for (int i = (playerStartingRound+1);i<playerStartingRound+playerCount;i++){
            if (cardSelected[i%playerCount]->val>cardSelected[winningHand]->val && cardSelected[i%playerCount]->suit == currentHandsSuit){
              winningHand = i%playerCount;
            }
          }
          players[winningHand].currentRoundHandsWon++;
          for (int i = 0; i<playerCount; i++){//resets and removes cards for next hand
            for (int l = 0; l<players[i].numCardsInHand-1; l++){
              if (players[i].hand[l]==cardSelected[i]){
                Card *temp = players[i].hand[l+1];
                players[i].hand[l+1]=cardSelected[i];
                players[i].hand[l]=temp;
              }
            }
            cardSelected[i]->isSelected = false;
            cardSelected[i]=NULL;
            players[i].numCardsInHand--;
          }
          selectedCount = 0;
          playbutt.isButtPressed=false;
           char t[40];
           snprintf(t, 40, "Player %d: %d", winningHand,
                   players[winningHand].currentPrediction);
           for (int i = 0; i<players[winningHand].currentRoundHandsWon;i++){
           sprintf(&t[11+(i*2)+(players[winningHand].currentPrediction/10)], " |");
          }
         if (players[0].numCardsInHand != 0){
          Texture_init_andLoadFromRenderedText(
              &playerText[winningHand], ctx->renderer, ctx->gFont,
              (SDL_FRect){15, 75 + (winningHand * 30), 230+(21*players[winningHand].currentRoundHandsWon), 35}, t, 11+(players[winningHand].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
              (SDL_Color){255, 255, 255, 255});
          playerStartingRound=winningHand;
          playerPlaying=winningHand;
        }
         else{
        Texture_init_andLoadFromRenderedText(
            &playerText[winningHand], ctx->renderer, ctx->gFont,
            (SDL_FRect){15, 75 + (winningHand * 30), 200+(21*players[winningHand].currentRoundHandsWon), 30}, t, 11+(players[winningHand].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
            (SDL_Color){255, 255, 255, 175});
      currentPhase = scoring;
      Texture_init_andLoadFromRenderedText(
          &phaseOrTurnText, ctx->renderer, ctx->gFont,
          (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
          "Scoring Phase", 13, (SDL_Color){255, 255, 255, 255});
         }
      }
      break;
    }

    if (playerPlaying == userPlaying) { //-----------------------PLAYER PLAY PHASE
      Player_UpdateHand(&players[userPlaying], &mousePos, &handLocation);//This lets user move cards around their hand
      if (playbutt.isButtPressed) {
        char t[40];
        snprintf(t, 40, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
           for (int i = 0; i<players[playerPlaying].currentRoundHandsWon;i++){
           sprintf(&t[11+(i*2)+(players[playerPlaying].currentPrediction/10)], " |");
          }
        Texture_init_andLoadFromRenderedText(
            &playerText[playerPlaying], ctx->renderer, ctx->gFont,
            (SDL_FRect){15, 75 + (playerPlaying * 30), 200+(21*players[playerPlaying].currentRoundHandsWon), 30}, t, 11+(players[playerPlaying].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
            (SDL_Color){255, 255, 255, 175});
        playerPlaying =
            (playerPlaying + 1 == playerCount) ? 0 : playerPlaying + 1;
        if (selectedCount != playerCount){
        snprintf(t, 40, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
           for (int i = 0; i<players[playerPlaying].currentRoundHandsWon;i++){
           sprintf(&t[11+(i*2)+(players[playerPlaying].currentPrediction/10)], " |");
          }
          Texture_init_andLoadFromRenderedText(
              &playerText[playerPlaying], ctx->renderer, ctx->gFont,
              (SDL_FRect){15, 75 + (playerPlaying * 30), 230+(21*players[playerPlaying].currentRoundHandsWon), 35}, t, 11+(players[playerPlaying].currentRoundHandsWon*2+(players[playerPlaying].currentPrediction/10)),
              (SDL_Color){255, 255, 255, 255});
      }
        // phase switches to scoring in render func
      }
    } else { //---------------------------------CPU PLAY PHASE
      if (ctx->frameCount % CPU_DELAY == 0) {
        // SDL_Log("Player %d: ", playerPlaying);
        // Player_PrintHand(&players[playerPlaying]);
        Uint8 ran = rand() % players[playerPlaying].numCardsInHand;
        players[playerPlaying].hand[ran]->isSelected = true;
        cardSelected[playerPlaying] = players[playerPlaying].hand[ran];
        char t[40];
        snprintf(t, 40, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
           for (int i = 0; i<players[playerPlaying].currentRoundHandsWon;i++){
           sprintf(&t[11+(i*2)+(players[playerPlaying].currentPrediction/10)], " |");
          }
        Texture_init_andLoadFromRenderedText(
            &playerText[playerPlaying], ctx->renderer, ctx->gFont,
            (SDL_FRect){15, 75 + (playerPlaying * 30), 200+(21*players[playerPlaying].currentRoundHandsWon), 30}, t, 11+(players[playerPlaying].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
            (SDL_Color){255, 255, 255, 175});
        playerPlaying =
            (playerPlaying + 1 == playerCount) ? 0 : playerPlaying + 1;
        if (selectedCount+1 != playerCount){
          snprintf(t, 40, "Player %d: %d", playerPlaying,
                 players[playerPlaying].currentPrediction);
           for (int i = 0; i<players[playerPlaying].currentRoundHandsWon;i++){
           sprintf(&t[11+(i*2)+(players[playerPlaying].currentPrediction/10)], " |");
          }
          Texture_init_andLoadFromRenderedText(
              &playerText[playerPlaying], ctx->renderer, ctx->gFont,
              (SDL_FRect){15, 75 + (playerPlaying * 30), 230+(21*players[playerPlaying].currentRoundHandsWon), 35}, t, 11+(players[playerPlaying].currentRoundHandsWon*2)+(players[playerPlaying].currentPrediction/10),
              (SDL_Color){255, 255, 255, 255});
        // phase switches to scoring in render func
      }
    }
    }
    break;
  case scoring:  //----------------------- UPDATE SCORING --------------------------
    if (ctx->frameCount % CPU_DELAY*3 == 0){
    playbutt.isButtPressed = false; //reset stuff


    char t[50];
    for (int i = 0; i<playerCount; i++){
      if (players[i].currentPrediction == players[i].currentRoundHandsWon){
        // SDL_Log("Player %d: earned %d points!\n",i, players[i].currentPrediction+round);
        if (round != 5) //double points for round 5
        players[i].points += (round+players[i].currentPrediction);
        else
        players[i].points += ((round+players[i].currentPrediction)*2);
      }
      players[i].currentRoundHandsWon = 0;
      players[i].currentPrediction = -1;
    snprintf(t, 50, "Player %d: %d", i, players[i].points);
      Texture_init_andLoadFromRenderedText(
          &playerPointText[i], ctx->renderer, ctx->gFont,
          (SDL_FRect){(SCREEN_WIDTH-170)-15, 15 + (i * 20), 170, 20}, t, 11+((players[i].points/10)),
          (SDL_Color){255, 200, 200, 255});
    }
    currentPhase = deal;
    }
    break;
  }
}

static void maingamescene_render(
    SDL_Renderer *renderer) { // -------------------------------------- RENDER

  // UI
  switch (currentPhase) {
  case deal:
    for (int i = 0; i < playerCount; i++) {
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL,
                     SDL_FLIP_NONE);
      Texture_render(&playerPointText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  case predict:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    Player_RenderHand(&players[userPlaying], renderer, &handLocation,
                      &playLocation);

    Texture_render(&phaseOrTurnText, renderer, NULL, NULL, 0.0, NULL,
                   SDL_FLIP_NONE);
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    if (playerPlaying == userPlaying)
      for (int i = 0; i < round + 1; i++) {
        if (!((playerPlaying+1)%playerCount==playerStartingPrediction&&combinedRoundPredictions + i == round)) {//dont render button if user is the last predicting and it equals the round prediction total by all players
          if (!(round == 1&&i==0))//dont render 0 when round is 1
        Button_render(&predictionButtons[i], renderer);
        }
      }
    for (int i = 0; i < playerCount; i++) {
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL,
                     SDL_FLIP_NONE);
      Texture_render(&playerPointText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  case play:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    Player_RenderHand(&players[userPlaying], renderer, &handLocation,
                      &playLocation);
    selectedCount = 0; // terrible way to do this, but is what it is.
    float gap =
        (playLocation.w - (CARDPXWIDTH * playerCount)) / (playerCount + 1);
    for (int i = playerStartingRound; i < playerStartingRound + playerCount;
         i++) {
      if (cardSelected[i % playerCount] != NULL) {
        cardSelected[i % playerCount]->pos.x = (playLocation.x) +
                                               (gap * ((i -playerStartingRound) + 1)) +
                                               (selectedCount * CARDPXWIDTH);
        cardSelected[i % playerCount]->pos.y = playLocation.y;
        Card_Render(cardSelected[i % playerCount], renderer);
        selectedCount++;
      }
    }

    // UI STUFF
    if (cardSelected[userPlaying] != NULL && userPlaying == playerPlaying && playbutt.isButtPressed == false)
      Button_render(&playbutt, renderer);

    Texture_render(&phaseOrTurnText, renderer, NULL, NULL, 0.0, NULL,
                   SDL_FLIP_NONE);
    // Texture_render(&currentPredictionText, renderer, NULL, NULL, 0.0, NULL,
    // SDL_FLIP_NONE);
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    for (int i = 0; i < playerCount; i++) {
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL,
                     SDL_FLIP_NONE);
      Texture_render(&playerPointText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  case scoring:
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderRect(renderer, &handLocation);
    SDL_RenderRect(renderer, &playLocation);
    // Player_RenderHand(&players[userPlaying], renderer, &handLocation,
    //                   &playLocation);
    //
    // for (int i = 0; i < playerCount; i++) {
    //   Card_Render(cardSelected[i], renderer);
    // }

    Texture_render(&phaseOrTurnText, renderer, NULL, NULL, 0.0, NULL,
                   SDL_FLIP_NONE);
    // Texture_render(&currentPredictionText, renderer, NULL, NULL, 0.0, NULL,
    // SDL_FLIP_NONE);
    Texture_render(&roundText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    for (int i = 0; i < playerCount; i++) {
      Texture_render(&playerText[i], renderer, NULL, NULL, 0.0, NULL,
                     SDL_FLIP_NONE);
      Texture_render(&playerPointText[i], renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
    break;
  }
}

static void getMousePos(SDL_Event *e);
static void maingamescene_events(
    SDL_Event *e) { // -------------------------------------------------  EVENTS
  getMousePos(e);
  switch (currentPhase) {
  case deal:
    break;
  case predict:
    if (playerPlaying == userPlaying)
      for (int i = 0; i < round + 1; i++) {
        if (!((playerPlaying+1)%playerCount==playerStartingPrediction&&combinedRoundPredictions + i == round)){ //dont hand button events if user is the last predicting and it equals the round prediction total by all players
          if (!(round == 1&&i==0))//dont render 0 when round is 1
        Button_handleEvent(&predictionButtons[i], e);
        }
      }
      for (int i = players[userPlaying].numCardsInHand - 1; i >= 0; i--) {
      Card_HandleEvents(players[userPlaying].hand[i], e, mousePos,
                        &playLocation, &cardBeingHeld,
                        &cardSelected[userPlaying]);
    }
    break;
  case play:
    if (!playbutt.isButtPressed)
    for (int i = players[userPlaying].numCardsInHand - 1; i >= 0; i--) {
      Card_HandleEvents(players[userPlaying].hand[i], e, mousePos,
                        &playLocation, &cardBeingHeld,
                        &cardSelected[userPlaying]);
    }
    if (cardSelected[userPlaying] != NULL && userPlaying == playerPlaying && playbutt.isButtPressed == false)
      Button_handleEvent(&playbutt, e);
    break;

  case scoring:
    break;
  }
}

static void
maingamescene_stop() { // --------------------------------------------STOP
  Button_free(&playbutt);
  for (int i = 0; i < PREDICTBUTTONAMOUNT; i++) {
    Button_free(&predictionButtons[i]);
  }
  for (int i = 0; i < playerCount; i++) {
    Texture_free(&playerText[i]);
    Texture_free(&playerPointText[i]);
  }
  free(playerText);
  free(playerPointText);
  free(cardSelected);
  Texture_free(&phaseOrTurnText);
  // Texture_free(&currentPredictionText);
  Texture_free(&roundText);
  Texture_free(&deck.spriteSheet);
  free(players);
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
