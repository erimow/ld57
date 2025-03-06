#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct {
  SDL_Texture *texture;
  SDL_FRect loc;
  float width;
  float height;
} Texture;

void Texture_init(Texture *texture);
void Texture_free(Texture *texture);
bool Texture_loadFromFile(Texture *texture, SDL_Renderer *renderer,
                          const char *path);
bool Texture_init_andLoadFromRenderedText(Texture *texture, SDL_Renderer *renderer,
                                  TTF_Font *gFont, SDL_FRect loc, const char *textureText,
                                  SDL_Color textColor);
bool Texture_loadFromRenderedText(Texture *texture, SDL_Renderer *renderer,
                                  TTF_Font *gFont, const char *textureText,
                                  SDL_Color textColor);

void Texture_setColor(Texture *texture, Uint8 red, Uint8 green, Uint8 blue);
void Texture_setBlendMode(Texture *texture, SDL_BlendMode blending);
void Texture_setAlpha(Texture *texture, Uint8 alpha);
void Texture_render(Texture *texture, SDL_Renderer *renderer, SDL_FRect *clip,
                    SDL_FRect *pos, double angle, SDL_FPoint *center,
                    SDL_FlipMode flip);
int Texture_getWidth(Texture *texture);
int Texture_getHeight(Texture *texture);

#endif /* Texture_h */
