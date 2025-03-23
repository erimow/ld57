#include <SDL3/SDL_stdinc.h>
#include <stdlib.h>
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

typedef enum ScenesEnum { MAINMENU, GAME } ScenesEnum;
//Store enum in context
typedef struct Scene{
   void (*loadAssets)(void *ctx);
   void (*start)(void *ctx);
   void (*stop)(void);
   bool isSceneLoaded;
}Scene;

typedef struct SceneManager{
   Scene* scenes;
   Uint8 numScenes;
   ScenesEnum currentScene;
}SceneManager;

void SceneManager_init(SceneManager* sm, int numScenes);
void SceneManager_deinit(SceneManager *sm);
void SceneManager_addScene(SceneManager* sm,ScenesEnum scene, void (*loadAssets)(void *ctx), void (*start)(void *ctx), void (*stop)(void));
void SceneManager_loadScene(SceneManager* sm, ScenesEnum scene, void *ctx);
void SceneManager_switchScene(SceneManager *sm, ScenesEnum scene, void *ctx);
void SceneManager_switchSceneAndUnload(SceneManager *sm, ScenesEnum scene, void *ctx);

bool SceneManager_isSceneAssetsLoaded(SceneManager *sm, ScenesEnum scene);

#endif
