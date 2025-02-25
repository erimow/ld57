#include <SDL3/SDL.h>
#include "../Engine/Texture.h"

#ifndef CARD_H
#define CARD_H

typedef struct Card {
  Texture CardBackdrop;
  SDL_FRect pos;
  SDL_FPoint whenSelectedMousePos;
  bool isSelected;
} Card;

void Card_HandleEvents(Card *c, SDL_Event *e, SDL_FPoint mousePos);
void Card_Render(Card *c, SDL_Renderer *renderer);

#endif // !CARD_H
