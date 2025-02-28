#include "../Engine/constants.h"
#include "card.h"
#include <SDL3/SDL.h>
#ifndef PLAYER_H
#define PLAYER_H
#define MAX_CARDS 10

typedef struct {
  Card *hand[MAX_CARDS];
  uint8_t numCardsInHand;
} Player;

void Player_Init(Player *p);
void Player_InitPlayers(Player *p, uint8_t numPlayers);
void Player_AddCard(Player *p, Card *c);
void Player_PlayCard(Player *p);
void Player_RenderHand(Player *p, SDL_Renderer *renderer,
                       SDL_FRect *handLocation);

#endif
