// #include "Button.h"
// #include "Texture.h"
// #include "Timer.h"
#include <SDL3/SDL.h>
#ifdef __linux__
#include <SDL3_image//SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_pixels.h>
// #include <SDL2/SDL_rect.h>
// #include <SDL2/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#elif defined __APPLE__
// #include <SDL2_image/SDL_image.h>
// #include <SDL2_mixer/SDL_mixer.h>
// #include <SDL2_ttf/SDL_ttf.h>
#endif

#ifndef CONTEXT_H
#define CONTEXT_H

typedef enum Scenes { MAINMENU, GAME } Scenes;
typedef struct context {
  /* Important stuff */
  int ticksPerFrame;
  SDL_Window *window;     // freed
  SDL_Renderer *renderer; // freed
  uint32_t width, height;

  /* Textures/Fonts */
  TTF_Font *gFont;     // freed
  // Texture fontTexture; // freed
  // Texture fpsTexture;  // freed

  /* Entities */

  /* Other */
  // Button butt;           // freed
  // SDL_Joystick *gamePad; // freed
  // Timer fps;             // no need to free
  // Timer capTimer;
  int frameCount;

  /* Music/Sounds */
  // Mix_Chunk *soundEffect; // freed
  // Mix_Music *gameMusic;   // freed

  // Other ctx stuff
  // SDL_FRect fpsLoc;
  // SDL_Color fpsCol;

  // bool isButtPressed;
  bool quit;


 Scenes currentScene; //Find scenes inside of context.h
} context;


#endif
