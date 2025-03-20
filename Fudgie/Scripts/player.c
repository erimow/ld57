#include "player.h"

void Player_Init(Player *p) {
  p->numCardsInHand = 0;
  p->points = 0;
  p->currentPrediction = -1;
  p->currentRoundHandsWon = 0;
}
void Player_InitPlayers(Player *p, uint8_t numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    Player_Init(&p[i]);
  }
}
void Player_AddCard(Player *p, Card *c) { p->hand[p->numCardsInHand++] = c; }
void Player_UpdateHand(Player *p, SDL_FPoint *mousePos,
                       SDL_FRect *handLocation) {
  for (int i = 0; i < p->numCardsInHand; i++) {
    Card *a = p->hand[i];
    if (a->isHeld) {
      a->pos.x = mousePos->x - a->whenHeldMousePos.x;
      a->pos.y = mousePos->y - a->whenHeldMousePos.y;
      if (p->numCardsInHand > 1 &&
          (a->pos.y + ((float)CARDPXHEIGHT / 2)) > handLocation->y) {
        if (i != 0) {
          if (a->pos.x + ((float)CARDPXWIDTH / 2) <
              p->hand[i - 1]->pos.x + ((float)CARDPXWIDTH / 2)) {
            p->hand[i] = p->hand[i - 1];
            p->hand[i - 1] = a;
          }
        }
        if (i != p->numCardsInHand - 1) {
          if (a->pos.x + ((float)CARDPXWIDTH / 2) >
              p->hand[i + 1]->pos.x + ((float)CARDPXWIDTH / 2)) {
            p->hand[i] = p->hand[i + 1];
            p->hand[i + 1] = a;
          }
        }
      }
    }
  }
}
void Player_RenderHand(Player *p, SDL_Renderer *renderer,
                       SDL_FRect *handLocation, SDL_FRect *playLocation) {
  Uint8 cardsInHand = p->numCardsInHand;
  unsigned int cardPxWidth = CARDPXWIDTH;
  unsigned int cardPxHeight = CARDPXHEIGHT;
  int spacingBetweenCards =
      (handLocation->w - (cardsInHand * cardPxWidth)) / cardsInHand;
  // SDL_Log("spaceBetween %d\n", spacingBetweenCards);
  for (int i = 0; i < cardsInHand; i++) {
    if (!p->hand[i]->isHeld && !p->hand[i]->isSelected) {
      p->hand[i]->pos.x =
          handLocation->x + (i * (cardPxWidth + spacingBetweenCards));
      p->hand[i]->pos.y =
          handLocation->y + ((float)(handLocation->h - cardPxHeight) / 2);
      Card_Render(p->hand[i], renderer);
    } else if (p->hand[i]->isHeld) {
      Card_Render(p->hand[i], renderer);
    }
  }
}

void Player_PrintHand(Player *p) {
  for (int i = 0; i < p->numCardsInHand; i++) {
    SDL_Log("Card: %d: suit: %c, val %d\n", i, p->hand[i]->suit,
            p->hand[i]->val);
  }
  SDL_Log("\n");
}
bool Player_UserPredict(context *ctx, Player *players, Uint8 *playerCount,
                        Uint8 *playerPlaying, Uint8 *round,
                        Uint8 *playerStartingPrediction,
                        Uint8 *playerStartingRound,
                        Uint8 *combinedRoundPredictions, Texture *playerText,
                        Texture *phaseOrTurnText, Button *predictionButtons) {
  bool result = false;
  for (int i = 0; i < *round + 1; i++) {
    if (predictionButtons[i].isButtPressed) {
      players[*playerPlaying].currentPrediction = i;
      *combinedRoundPredictions += i;
      predictionButtons[i].isButtPressed = false;
      char t[22];
      snprintf(t, 22, "Player %d: %d", *playerPlaying, i);
      Texture_init_andLoadFromRenderedText(
          &playerText[*playerPlaying], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (*playerPlaying * 30), 200, 30}, t,
          11 + (players[*playerPlaying].currentPrediction / 10),
          (SDL_Color){255, 255, 255, 175});
      // Texture_init_andLoadFromRenderedText(
      // &phaseOrTurnText, ctx->renderer, ctx->gFont,
      // (SDL_FRect){((float)SCREEN_WIDTH/2)-125, 15, 250, 60}, "Player 1's
      // Turn", 15, (SDL_Color){255, 255, 255, 255});
      *playerPlaying =
          (*playerPlaying + 1 == *playerCount) ? 0 : *playerPlaying + 1;
      if (*playerPlaying == *playerStartingPrediction) {
        result = true;
        Texture_init_andLoadFromRenderedText(
            phaseOrTurnText, ctx->renderer, ctx->gFont,
            (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60},
            "Play Phase", 10 + (players[*playerPlaying].currentPrediction / 10),
            (SDL_Color){255, 255, 255, 255});
        Uint8 highestPredictionByPlayer = *playerStartingPrediction;
        for (int i = *playerStartingPrediction + 1;
             i < *playerStartingPrediction + *playerCount; i++) {
          if (players[i % *playerCount].currentPrediction >
              players[highestPredictionByPlayer].currentPrediction) {
            highestPredictionByPlayer = i % *playerCount;
          }
        }
        *playerStartingPrediction =
            (*playerStartingPrediction + 1) % *playerCount;
        *playerPlaying = highestPredictionByPlayer;
        *playerStartingRound = *playerPlaying;
      }
      snprintf(t, 22, "Player %d: %d", *playerPlaying,
               players[*playerPlaying].currentPrediction);
      Texture_init_andLoadFromRenderedText(
          &playerText[*playerPlaying], ctx->renderer, ctx->gFont,
          (SDL_FRect){15, 75 + (*playerPlaying * 30), 230, 35}, t,
          11 + (players[*playerPlaying].currentPrediction / 10),
          (SDL_Color){255, 255, 255, 255});
    }
  }

  return result;
}

bool Player_CPUPredict(context *ctx, Player *players, Uint8 *playerCount,
                       Uint8 *playerPlaying, Uint8 *round,
                       Uint8 *playerStartingPrediction,
                       Uint8 *playerStartingRound,
                       Uint8 *combinedRoundPredictions, Texture *playerText,
                       Texture *phaseOrTurnText) {
  bool result = false;

  char t[40];
  players[*playerPlaying].currentPrediction =
      rand() % (*round + 1); // makes random prediction
  if ((*playerPlaying + 1) % *playerCount == *playerStartingPrediction) {
    while (players[*playerPlaying].currentPrediction +
               *combinedRoundPredictions ==
           *round) {
      players[*playerPlaying].currentPrediction =
          rand() % (*round + 1); // makes random prediction
    }
  }
  if (*round == 1 && players[*playerPlaying].currentPrediction != 1)
    players[*playerPlaying].currentPrediction =
        1; // SET PREDICTION TO 1 WHEN ROUND IS 1

  *combinedRoundPredictions += players[*playerPlaying].currentPrediction;
  snprintf(t, 40, "Player %d: %d", *playerPlaying,
           players[*playerPlaying].currentPrediction);
  Texture_init_andLoadFromRenderedText(
      &playerText[*playerPlaying], ctx->renderer, ctx->gFont,
      (SDL_FRect){15, 75 + (*playerPlaying * 30), 200, 30}, t,
      11 + (players[*playerPlaying].currentRoundHandsWon * 2) +
          (players[*playerPlaying].currentPrediction / 10),
      (SDL_Color){255, 255, 255, 175});
  *playerPlaying =
      (*playerPlaying + 1 == *playerCount) ? 0 : *playerPlaying + 1;
  if (*playerPlaying == *playerStartingPrediction) {
    Uint8 highestPredictionByPlayer = 0;
    for (int i = *playerStartingPrediction + 1;
         i < *playerStartingPrediction + *playerCount; i++) {
      if (players[i % *playerCount].currentPrediction >
          players[highestPredictionByPlayer].currentPrediction) {
        highestPredictionByPlayer = i % *playerCount;
      }
    }
    *playerStartingPrediction = (*playerStartingPrediction + 1) % *playerCount;
    *playerPlaying = highestPredictionByPlayer;
    *playerStartingRound = *playerPlaying;

    Texture_init_andLoadFromRenderedText(
        phaseOrTurnText, ctx->renderer, ctx->gFont,
        (SDL_FRect){((float)SCREEN_WIDTH / 2) - 125, 15, 250, 60}, "Play Phase",
        10, (SDL_Color){255, 255, 255, 255});
    result = true;
  }
  snprintf(t, 22, "Player %d: %d", *playerPlaying,
           players[*playerPlaying].currentPrediction);
  Texture_init_andLoadFromRenderedText(
      &playerText[*playerPlaying], ctx->renderer, ctx->gFont,
      (SDL_FRect){15, 75 + (*playerPlaying * 30), 230, 35}, t,
      11 + (players[*playerPlaying].currentPrediction / 10),
      (SDL_Color){255, 255, 255, 255});

  return result;
}

bool Player_CPUPlay(context *ctx, Player *players, Uint8 *playerCount,
                    Uint8 *playerPlaying, Uint8 *round,
                    Uint8 *playerStartingPrediction, Uint8 *playerStartingRound,
                    Uint8 *combinedRoundPredictions, Texture *playerText,
                    Texture *phaseOrTurnText) {
  bool result = false;

  return result;
}
