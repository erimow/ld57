//
//  Tilemap.h
//  CSDL
//
//  Created by Erik Morris on 7/23/24.
//

#ifndef Tilemap_h
#define Tilemap_h

#include <stdio.h>
#include "constants.h"
#include "Texture.h"
#include <SDL2/SDL.h>

//SDL_Point neighbor_offsets[9] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {0, 0}, {-1, 1}, {0, 1}, {1, 1}};

typedef struct{
    int xGridPos, yGridPos;
    int spriteXId, spriteYId;
    SDL_FRect pos;
    SDL_RendererFlip flip;
    double rotation;
}Tile;

typedef struct{
    Texture* spriteSheet;
    Tile* tiles;
    char* tileTypesForParse;
    int numTileTypesForParse;
    SDL_FRect* colliders;
    int tileAmount;
    int mapWidth, mapHeight;
    float scale;
}Tilemap;

void Tile_init(Tile* tile, int xGridPos, int yGridPos, int spriteXId, int spriteYId, int tileSize, int mapHeight, float scale, double rotation, SDL_RendererFlip flip);
void Tile_free(Tile* tile);
void Tilemap_init(Tilemap* tm, Texture* text, float scale, char* fileName, char* tileTypes, int numTileTypes);
void Tilemap_free(Tilemap* tm);
void Tilemap_populate(Tilemap* tm, char* file);
void Tilemap_render(Tilemap* tm, SDL_Renderer* renderer, float xOffset, float yOffset);
SDL_FRect* Tilemap_getColliders(Tilemap* tm);
bool Tilemap_isTileParseable(Tilemap* tm, char tileToParse, int* tileId);

#endif /* Tilemap_h */
