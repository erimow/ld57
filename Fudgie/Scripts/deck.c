#include "deck.h"

static uint8_t cardPxWidth = CARDPXWIDTH;
static uint8_t cardPxHeight = CARDPXHEIGHT;

void Deck_init(Deck *d) {
  d->cardsRemainingInDeck = 52;
  char suit;
  uint8_t val;
  SDL_FRect defaultPos = {0, 0, cardPxWidth, cardPxHeight};
  for (int i = 0; i < 52; i++) {
    switch (i / 13) {
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
    switch (i % 13) {
    case 0:
      val = 'A';
      break;
    case 10:
      val = 'J';
      break;
    case 11:
      val = 'Q';
      break;
    case 12:
      val = 'K';
      break;
    default:
      val = (i % 13) + 1;
      break;
    }
    d->cards[i].suit = suit;
    d->cards[i].val = val;
    d->cards[i].clip =
        (SDL_FRect){(i % 13) * cardPxWidth, (i / 13) * cardPxHeight,
                    cardPxWidth, cardPxHeight};
    d->cards[i].pos = defaultPos;
    d->cards[i].CardSpritesheet = &d->spriteSheet;
    d->cards[i].isSelected = false;
    d->cards[i].isHeld = false;
    d->cards[i].isFront = true;
    // printf("Card: %d, val: %c, suit: %c\n", i, val, suit);
  }
}

void Deck_scramble(Deck *d) {
  for (int i = 0; i < 52; i++) {
    Card swap = d->cards[i];
    int ran = (rand() % 52);
    d->cards[i] = d->cards[ran];
    d->cards[ran] = swap;
  }
}

void Deck_deal(Deck *d, Player *players, uint8_t numPlayers,
               uint8_t numCardsToDealForEachPlayer) {
  for (int l = 0; l < numCardsToDealForEachPlayer; l++)
    for (int i = 0; i < numPlayers; i++) {
      if (d->cardsRemainingInDeck > 0) {
        Player_AddCard(&players[i], &d->cards[(--d->cardsRemainingInDeck)]);
      } else {
        printf("No cards remaining in deck!!!\n");
      }
    }
}
