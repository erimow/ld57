#include "scenemanager.h"

void SceneManager_init(SceneManager* sm, int numScenes){
    sm->scenes = malloc(sizeof(Scene)*numScenes);
    sm->numScenes = numScenes;
    for (int i = 0; i<numScenes; i++){
        sm->scenes[i].isSceneLoaded=false;
        sm->scenes[i].loadAssets = NULL;
        sm->scenes[i].start = NULL;
        sm->scenes[i].stop = NULL;
    }
}
void SceneManager_deinit(SceneManager *sm){
    free(sm->scenes);
}
void SceneManager_addScene(SceneManager *sm, ScenesEnum scene, void (*loadAssets)(void *ctx), void (*start)(void *ctx), void (*stop)(void)){
    sm->scenes[scene].loadAssets=loadAssets;
    sm->scenes[scene].start=start;
    sm->scenes[scene].stop=stop;
}
void SceneManager_loadScene(SceneManager* sm, ScenesEnum scene, void *ctx){
    // sm->currentScene = scene;
    if(!sm->scenes[scene].isSceneLoaded){
        sm->scenes[scene].loadAssets(ctx);
        sm->scenes[scene].isSceneLoaded=true;
    }
}
void SceneManager_switchScene(SceneManager *sm, ScenesEnum scene, void *ctx){
   sm->currentScene = scene; //then loads assets if needed and runs start function
    if(!sm->scenes[scene].isSceneLoaded){
        sm->scenes[scene].loadAssets(ctx);
        sm->scenes[scene].isSceneLoaded=true;
    }
   sm->scenes[sm->currentScene].start(ctx);
}
void SceneManager_switchSceneAndUnload(SceneManager *sm, ScenesEnum scene, void *ctx){
     sm->scenes[sm->currentScene].stop();
    sm->scenes[sm->currentScene].isSceneLoaded = false; //unloads previous scene

   sm->currentScene = scene; //then loads assets if needed and runs start function
    if(!sm->scenes[scene].isSceneLoaded){
        sm->scenes[scene].loadAssets(ctx);
        sm->scenes[scene].isSceneLoaded=true;
    }
   sm->scenes[sm->currentScene].start(ctx);

}



bool SceneManager_isSceneAssetsLoaded(SceneManager *sm, ScenesEnum scene){
    return sm->scenes[scene].isSceneLoaded;
}
