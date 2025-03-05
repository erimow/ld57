#include <SDL3/SDL.h>
#include "../Engine/Texture.h"

#ifndef CARD_H
#define CARD_H

typedef struct Card {
  Texture *CardSpritesheet;
  SDL_FRect clip;
  SDL_FRect pos;
  SDL_FPoint whenHeldMousePos;
  bool isSelected;
  bool isHeld;
  char suit;
  char val;
} Card;

void Card_HandleEvents(Card *c, SDL_Event *e, SDL_FPoint mousePos, SDL_FRect *playZone, Card *cardHeld, Card *cardSelected);
void Card_Render(Card *c, SDL_Renderer *renderer);

#endif // !CARD_H
