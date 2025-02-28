#include "player.h"

void Player_Init(Player *p) { p->numCardsInHand = 0; }
void Player_InitPlayers(Player *p, uint8_t numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    Player_Init(&p[i]);
  }
}
void Player_AddCard(Player *p, Card *c) { p->hand[p->numCardsInHand++] = c; }
void Player_RenderHand(Player *p, SDL_Renderer *renderer,
                       SDL_FRect *handLocation) {
  SDL_Log("Debug\n");
  Uint8 cardsInHand = p->numCardsInHand;
  unsigned int cardPxWidth = CARDPXWIDTH;
  unsigned int cardPxHeight = CARDPXHEIGHT;
  int spacingBetweenCards =
      (handLocation->w - (cardsInHand * cardPxWidth)) / cardsInHand;
  SDL_Log("spaceBetween %d\n", spacingBetweenCards);
  for (int i = 0; i < cardsInHand; i++) {
    if (!p->hand[i]->isSelected) {
      p->hand[i]->pos.x =
          handLocation->x + (i * (cardPxWidth + spacingBetweenCards));
      p->hand[i]->pos.y =
          handLocation->y + ((float)(handLocation->h - cardPxHeight) / 2);
    }
    SDL_Log("break\n");
    Card_Render(p->hand[i], renderer);
    SDL_Log("break\n");
  }
}
