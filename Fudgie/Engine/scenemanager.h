#include "context.h"
#include <SDL3/SDL_stdinc.h>
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

typedef struct Scene{
   void (*loadAssets)(context *ctx);
   void (*start)(void);
   void (*stop)(void);
}Scene;

typedef struct SceneManager{
   Scene* scenes;
   Uint8 numScenes;
}SceneManager;

void SceneManager_init(SceneManager* sm);
void SceneManager_deinit(SceneManager *sm);
void SceneManager_addScene(void (*loadAssets)(context *ctx), void (*start)(void), void (*stop)(void));
void SceneManager_switchScene(Scene* scene);

#endif
