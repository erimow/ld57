#include "player.h"

void Player_Init(Player *p) { p->numCardsInHand = 0; }
void Player_InitPlayers(Player *p, uint8_t numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    Player_Init(&p[i]);
  }
}
void Player_AddCard(Player *p, Card *c) { p->hand[p->numCardsInHand++] = c; }
