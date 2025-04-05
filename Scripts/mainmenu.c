
#include "../Engine/Button.h"
#include "../Engine/Texture.h"
#include "../Engine/constants.h"
#include "../Engine/context.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

static Texture titleImage;
static Button playButton;

static void mainmenuscene_loadAssets(void *ct) {
  context *ctx = (context*)ct;
  Texture_init(&titleImage);
  Texture_loadFromFile(&titleImage, ctx->renderer, "Art/titleimage.png");
  Button_initAndLoad(
        &playButton, ctx->renderer,
        (SCREEN_WIDTH/6)-100, (float)SCREEN_HEIGHT / 5,
        200, (float)SCREEN_HEIGHT / 7, "Art/ButtonBackground.png",
        ctx->gFont, "Play", 4, (SDL_Color){10, 90, 255, 255});
}

static void mainmenuscene_start(void *ct) {}

static void mainmenuscene_update(context *ctx) {
    if (playButton.isButtPressed) {
      SDL_Log("Switching to game scene\n");
      SceneManager_switchScene(&ctx->sm, GAME, ctx);
  }
}

static void mainmenuscene_render(SDL_Renderer *renderer) {
  // SDL_SetRenderDrawColor(renderer, );
  // SDL_RenderClear(renderer);
  Texture_render(&titleImage, renderer, NULL, &(SDL_FRect){0,0,SCREEN_WIDTH, SCREEN_HEIGHT}, 0.0, NULL, SDL_FLIP_NONE);
    Button_render(&playButton, renderer);
}

static void mainmenuscene_stop() {
  Texture_free(&titleImage);
  Button_free(&playButton);
}

static void mainmenuscene_handleEvents(SDL_Event *e) {
  Button_handleEvent(&playButton, e);
}
