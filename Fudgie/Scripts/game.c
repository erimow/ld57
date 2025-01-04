#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct card {
  Texture CardBackdrop;
  SDL_FRect pos;
  bool isSelected;
} card;

static SDL_FPoint whenSelectedMousePos;
static SDL_FPoint mousePos;
static card c;

static void loadAssets(context *ctx) {
  if (!Texture_loadFromFile(&c.CardBackdrop, ctx->renderer,
                            "Art/CardBackdrop.png"))
    printf("Could not load CardBackdrop\n");
}

static void Game_Start(context *ctx) {
  loadAssets(ctx);
  c.isSelected = false;
  c.pos = (SDL_FRect){400, 100, 100, 250};
}

static void Game_Update(context *ctx) {
  if (c.isSelected) {
    c.pos.x = mousePos.x - whenSelectedMousePos.x;
    c.pos.y = mousePos.y - whenSelectedMousePos.y;
  }
}

static void Game_Render(context *ctx) {
  Texture_render(&c.CardBackdrop, ctx->renderer, NULL, &c.pos, 0.0, NULL,
                 SDL_FLIP_NONE);
}

static void Game_Stop(context *ctx) {
  printf("stopping game\n");
  Texture_free(&c.CardBackdrop);
  printf("game assets stopped\n");
}

static void Game_Events(context *ctx, SDL_Event *e) {
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP) {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);
    mousePos.x = x;
    mousePos.y = y;
    // Check if mouse is in button
    bool inside = true;

    // Mouse is left of the button
    if (x < c.pos.x) {
      inside = false;
    }
    // Mouse is right of the button
    else if (x > c.pos.x + c.pos.w) {
      inside = false;
    }
    // Mouse above the button
    else if (y < c.pos.y) {
      inside = false;
    }
    // Mouse below the button
    else if (y > c.pos.y + c.pos.h) {
      inside = false;
    }
    // Mouse is outside button
    if (!inside) {
      Texture_setColor(&c.CardBackdrop, 255, 255, 255);
    }
    // Mouse is inside button
    else {
      // Set mouse over sprite
      switch (e->type) {
      case SDL_MOUSEMOTION:
        Texture_setColor(&c.CardBackdrop, 200, 200, 200);
        break;

      case SDL_MOUSEBUTTONDOWN:
        Texture_setColor(&c.CardBackdrop, 130, 130, 130);
        c.isSelected = !c.isSelected;
        whenSelectedMousePos = (SDL_FPoint){x - c.pos.x, y - c.pos.y};
        break;

      case SDL_MOUSEBUTTONUP:
        Texture_setColor(&c.CardBackdrop, 200, 200, 200);
        // c.isSelected = false;
        break;
      }
    }
  }
}
