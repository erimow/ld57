#include "../Engine/constants.h"
#include "card.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#ifndef PLAYER_H
#define PLAYER_H
#define MAX_CARDS 8

typedef struct {
  Card *hand[MAX_CARDS];
  uint8_t numCardsInHand;
  uint8_t points;
} Player;

void Player_Init(Player *p);
void Player_InitPlayers(Player *p, uint8_t numPlayers);
void Player_AddCard(Player *p, Card *c);
void Player_PlayCard(Player *p);
void Player_RenderHand(Player *p, SDL_Renderer *renderer,
                       SDL_FRect *handLocation, SDL_FRect *playLocation);

#endif
