#include "../Engine/context.h"
#include "../Engine/efuncs.h"
#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <string.h>

typedef struct card {
  Texture CardBackdrop;
  fvec2 position;
} card;

static card c;

static void Game_Start(context *ctx) {}

static void Game_Update(context *ctx) {}

static void Game_Events(context *ctx, SDL_Event *e) {}

static void Game_Render(context *ctx) {}

static void Game_Stop(context *ctx) {
  printf("stopping game\n");
  printf("game assets stopped\n");
}
