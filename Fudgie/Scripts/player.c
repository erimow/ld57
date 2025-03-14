#include "player.h"

void Player_Init(Player *p) { p->numCardsInHand = 0; p->points=0; p->currentPrediction=-1; p->currentRoundHandsWon = 0;}
void Player_InitPlayers(Player *p, uint8_t numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    Player_Init(&p[i]);
  }
}
void Player_AddCard(Player *p, Card *c) { p->hand[p->numCardsInHand++] = c; }
void Player_UpdateHand(Player *p, SDL_FPoint *mousePos, SDL_FRect *handLocation){
   for (int i = 0; i < p->numCardsInHand; i++) {
        Card *a = p->hand[i];
        if (a->isHeld) {
          a->pos.x = mousePos->x - a->whenHeldMousePos.x;
          a->pos.y = mousePos->y - a->whenHeldMousePos.y;
          if (p->numCardsInHand > 1 &&
              (a->pos.y + ((float)CARDPXHEIGHT / 2)) > handLocation->y) {
            if (i != 0) {
              if (a->pos.x + ((float)CARDPXWIDTH / 2) <
                  p->hand[i - 1]->pos.x +
                      ((float)CARDPXWIDTH / 2)) {
                p->hand[i] = p->hand[i - 1];
                p->hand[i - 1] = a;
              }
            }
            if (i != p->numCardsInHand - 1) {
              if (a->pos.x + ((float)CARDPXWIDTH / 2) >
                  p->hand[i + 1]->pos.x +
                      ((float)CARDPXWIDTH / 2)) {
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
    }
    else if(p->hand[i]->isHeld){
      Card_Render(p->hand[i], renderer);
    }

  }
}
