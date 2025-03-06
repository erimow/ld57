#include "card.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void Card_Render(Card *c, SDL_Renderer *renderer) {
  // printf("x: %f, y: %f\n", c->pos.x, c->pos.y);
  Texture_render(c->CardSpritesheet, renderer, &c->clip, &c->pos, 0.0, NULL,
                 SDL_FLIP_NONE);
}
void Card_HandleEvents(Card *c, SDL_Event *e, SDL_FPoint mousePos,
                       SDL_FRect *playZone, Card **cardHeld,
                       Card **cardSelected) {
  if (e->type == SDL_EVENT_MOUSE_MOTION ||
      e->type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
      e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    // Get mouse position
    int x, y;
    x = mousePos.x;
    y = mousePos.y;
    // Check if mouse is in card
    bool inside = true;

    // Mouse is left of the card
    if (x < c->pos.x) {
      inside = false;
    }
    // Mouse is right of the card
    else if (x > c->pos.x + c->pos.w) {
      inside = false;
    }
    // Mouse above the card
    else if (y < c->pos.y) {
      inside = false;
    }
    // Mouse below the card
    else if (y > c->pos.y + c->pos.h) {
      inside = false;
    }
    // Mouse is outside card
    if (e->type == SDL_EVENT_MOUSE_BUTTON_UP && c->isHeld) {
      c->isHeld = false;
      *cardHeld = NULL;
    }
    if (!inside) {
      // Texture_setColor(
      //     c->CardSpritesheet, 255, 255,
      //     255); // This could potentially be inefficient.. not sure.
    }
    // Mouse is inside card
    else {
      // Set mouse over sprite
      switch (e->type) {
      case SDL_EVENT_MOUSE_MOTION:
        break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        // Texture_setColor(c->CardSpritesheet, 130, 130, 130);
        if (*cardHeld == NULL) {
          c->isHeld = true;
          *cardHeld = c;
          c->whenHeldMousePos = (SDL_FPoint){x - c->pos.x, y - c->pos.y};
          if (c->isSelected) {
            c->isSelected = false;
            (*cardSelected) = NULL;
          }
        }
        break;

      case SDL_EVENT_MOUSE_BUTTON_UP:
        // Texture_setColor(c->CardSpritesheet, 200, 200, 200);
        if (SDL_PointInRectFloat(&mousePos, playZone)) {
          if (*cardSelected != NULL) {
            (*cardSelected)->isSelected = false;
            (*cardSelected)->pos.y += 10000; // Ensures the previously selected
                                             // card is properly removed
            *cardSelected = NULL;
          }
          c->isSelected = true;
          *cardSelected = c;
        } else
          c->isSelected = false;
        break;
      }
    }
  }
}
