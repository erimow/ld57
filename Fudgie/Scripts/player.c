#include "player.h"

void Player_Init(Player *p) { p->numCardsInHand = 0; p->points=0;}
void Player_InitPlayers(Player *p, uint8_t numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    Player_Init(&p[i]);
  }
}
void Player_AddCard(Player *p, Card *c) { p->hand[p->numCardsInHand++] = c; }
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
    }
    else if (p->hand[i]->isSelected){
       p->hand[i]->pos.x =
          playLocation->x + (playLocation->w/2)-((float)cardPxWidth/2);
      p->hand[i]->pos.y =
          playLocation->y + ((float)(handLocation->h - cardPxHeight) / 2);
    }
    Card_Render(p->hand[i], renderer);
  }
}
