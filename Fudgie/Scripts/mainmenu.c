
#include "../Engine/Button.h"
#include "../Engine/Texture.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"
#include "card.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define BUTTONAMOUNT 3
static const Uint16 buttonW = 150;
static const Uint16 buttonGap =
    (SCREEN_WIDTH - (buttonW * BUTTONAMOUNT)) / (BUTTONAMOUNT + 1);
static Texture titleText;
static Button playerAmountButtons[BUTTONAMOUNT];

static void mainmenuscene_loadAssets(context *ctx) {
  Texture_init_andLoadFromRenderedText(
      &titleText, ctx->renderer, ctx->gFont,
      (SDL_FRect){((float)SCREEN_WIDTH / 2) - (float)SCREEN_WIDTH / 4,
                  (float)SCREEN_HEIGHT / 6, (float)SCREEN_WIDTH / 2,
                  (float)SCREEN_WIDTH / 4},
      "Fudgie!", 7, (SDL_Color){255, 255, 255, 255});
  for (int i = 0; i < BUTTONAMOUNT; i++) {
    char playerCount[2];
    snprintf(playerCount, 2, "%d", i + 3);
    Button_initAndLoad(
        &playerAmountButtons[i], ctx->renderer,
        (buttonGap * (i + 1)) + (buttonW * i), (float)SCREEN_HEIGHT / 1.5,
        buttonW, (float)SCREEN_HEIGHT / 7, "Art/ButtonBackground.png",
        ctx->gFont, playerCount, 1, (SDL_Color){255, 255, 255, 255});
  }
}

static void mainmenuscene_start() {}

static void mainmenuscene_update(context *ctx) {
  for (int i = 0; i < BUTTONAMOUNT; i++) {
    if (playerAmountButtons[i].isButtPressed) {
      printf("player amount -> %d\n", i + 3);
      ctx->currentScene = GAME;
    }
  }
}

static void mainmenuscene_render(SDL_Renderer *renderer) {
  // SDL_SetRenderDrawColor(renderer, );
  // SDL_RenderClear(renderer);
  Texture_render(&titleText, renderer, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
  for (int i = 0; i < BUTTONAMOUNT; i++) {
    Button_render(&playerAmountButtons[i], renderer);
  }
}

static void mainmenuscene_stop() {
  Texture_free(&titleText);
  for (int i = 0; i < BUTTONAMOUNT; i++) {
    Button_free(&playerAmountButtons[i]);
  }
}

static void mainmenuscene_handleEvents(SDL_Event *e) {
  for (int i = 0; i < BUTTONAMOUNT; i++) {
    Button_handleEvent(&playerAmountButtons[i], e);
  }
}
