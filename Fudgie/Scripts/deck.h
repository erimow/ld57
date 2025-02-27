#include <SDL3/SDL.h>
#include "card.h"
#ifndef DECK_H
#define DECK_H
typedef struct{
    Card cards[52];
    Texture spriteSheet;

} Deck;

    void Deck_init(Deck *d);
    void Deck_scramble(Deck *d);
    void Deck_deal(Deck *d, uint8_t numPlayers);
    void Deck_deinit(Deck *d);

#endif
