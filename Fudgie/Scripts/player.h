#include <SDL3/SDL.h>
#include <cstdint>
#include "card.h"
#ifndef PLAYER_H
#define PLAYER_H
#define MAX_CARDS 10


typedef struct {
    Card hand[MAX_CARDS];
    uint8_t numCardsInHand;
}Player;

#endif
