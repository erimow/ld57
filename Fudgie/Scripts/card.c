#include "card.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <stdbool.h>
#include <stdio.h>

void Card_Render(Card *c, SDL_Renderer *renderer) {
  Texture_render(c->CardSpritesheet, renderer, &c->clip, &c->pos, 0.0, NULL,
                 SDL_FLIP_NONE);
  // SDL_RenderFillRect(renderer, &c->pos);
}
void Card_HandleEvents(Card *c, SDL_Event *e, SDL_FPoint mousePos) {
  if (e->type == SDL_EVENT_MOUSE_MOTION || e->type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
      e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
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
          c->CardSpritesheet, 255, 255,
          255); // This could potentially be inefficient.. not sure.
    }
    // Mouse is inside button
    else {
      // Set mouse over sprite
      switch (e->type) {
      case SDL_EVENT_MOUSE_MOTION:
        break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        Texture_setColor(c->CardSpritesheet, 130, 130, 130);
        c->isSelected = true;
        c->whenSelectedMousePos = (SDL_FPoint){x - c->pos.x, y - c->pos.y};
        break;

      case SDL_EVENT_MOUSE_BUTTON_UP:
        Texture_setColor(c->CardSpritesheet, 200, 200, 200);
        c->isSelected = false;
        break;
      }
    }
  }
}
