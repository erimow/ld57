#include "../Engine/Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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
