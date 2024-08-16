//
//  Camera.h
//  CSDL
//
//  Created by Erik Morris on 7/19/24.
//

#ifndef Camera_h
#define Camera_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "Entity.h"

typedef struct{
    float xPos, yPos;
    float xCamOffset, yCamOffset;
}Camera;

void Camera_init(Camera* camera);
void Camera_free(Camera* camera);

void Camera_followEntity(Camera* camera, Entity* entity);

void Camera_setPosition(Camera* camera, float x, float y);
void Camera_setCameraOffset(Camera* camera, float x, float y);
void Camera_getPosition(Camera* camera, float* xPos, float*yPos);
void Camera_getObjectOffset(Camera* camera, float* xPos, float*yPos);
void Camera_getCameraOffset(Camera* camera, float* x, float*y);






#endif /* Camera_h */
