#include "card.h"
#include "player.h"
#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DECK_H
#define DECK_H
typedef struct {
  Card cards[52];
  uint8_t cardsRemainingInDeck;
  Texture spriteSheet;

} Deck;

void Deck_init(Deck *d);
void Deck_scramble(Deck *d);
void Deck_deal(Deck *d, Player *players, uint8_t numPlayers,
               uint8_t numCardsToDealForEachPlayer);
void Deck_deinit(Deck *d);

#endif
