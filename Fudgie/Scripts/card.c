#include "card.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdio.h>

void Card_Render(Card *c, SDL_Renderer *renderer) {
  Texture_render(&c->CardBackdrop, renderer, NULL, &c->pos, 0.0, NULL,
                 SDL_FLIP_NONE);
}
void Card_HandleEvents(Card *c, SDL_Event *e, SDL_FPoint mousePos) {
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    x = mousePos.x;
    y = mousePos.y;
    // Check if mouse is in button
    bool inside = true;

    // Mouse is left of the button
    if (x < c->pos.x) {
      inside = false;
    }
    // Mouse is right of the button
    else if (x > c->pos.x + c->pos.w) {
      inside = false;
    }
    // Mouse above the button
    else if (y < c->pos.y) {
      inside = false;
    }
    // Mouse below the button
    else if (y > c->pos.y + c->pos.h) {
      inside = false;
    }
    // Mouse is outside button
    if (!inside) {
      Texture_setColor(
          &c->CardBackdrop, 255, 255,
          255); // This could potentially be inefficient.. not sure.
    }
    // Mouse is inside button
    else {
      // Set mouse over sprite
      switch (e->type) {
      case SDL_MOUSEMOTION:
        Texture_setColor(&c->CardBackdrop, 200, 200, 200);
        break;

      case SDL_MOUSEBUTTONDOWN:
        Texture_setColor(&c->CardBackdrop, 130, 130, 130);
        c->isSelected = true;
        c->whenSelectedMousePos = (SDL_FPoint){x - c->pos.x, y - c->pos.y};
        break;

      case SDL_MOUSEBUTTONUP:
        Texture_setColor(&c->CardBackdrop, 200, 200, 200);
        c->isSelected = false;
        break;
      }
    }
  }
}
