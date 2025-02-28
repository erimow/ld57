#include "deck.h"


static uint8_t CARDPXWIDTH = 125;
static uint8_t CARDPXHEIGHT = 175;

void Deck_init(Deck *d){
    char suit;
    uint8_t val;
    for (int i = 0; i<52; i++){
        switch (i/13){
            case 0:
                suit = 's';
                break;
            case 1:
                suit = 'c';
                break;
            case 2:
                suit = 'd';
                break;
            case 3:
                suit = 'h';
                break;

        }
        switch(i%13){
            case 0:
                val='A';
                break;
            case 10:
                val='J';
                break;
            case 11:
                val='Q';
                break;
            case 12:
                val='K';
                break;
            default:
                val=(i%13)+1;
                break;
        }
        d->cards[i].suit = suit;
        d->cards[i].val = val;
        d->cards[i].clip = (SDL_FRect){(i%13)*CARDPXWIDTH, (i/13)*CARDPXHEIGHT, CARDPXWIDTH, CARDPXHEIGHT};
        d->cards[i].CardSpritesheet = &d->spriteSheet;
        d->cards[i].isSelected = false;
        // printf("Card: %d, val: %c, suit: %c\n", i, val, suit);
    }
}

void Deck_scramble(Deck *d){
  for (int i = 0; i < 52; i++){
      Card swap = d->cards[i];
      int ran = (rand() % 52);
}
}
