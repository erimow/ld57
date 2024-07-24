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
    int spriteId;
}Tile;

typedef struct{
    Texture* spriteSheet;
    Tile* tiles;
    int tileAmount;
    int mapWidth, mapHeight;
}Tilemap;

void Tile_init(Tile* tile, int xGridPos, int yGridPos, int spriteId);
void Tile_free(Tile* tile);
void Tilemap_init(Tilemap* tm, Texture* text, char* fileName);
void Tilemap_free(Tilemap* tm);
void Tilemap_populate(Tilemap* tm, char* file);
void Tilemap_render(Tilemap* tm, SDL_Renderer* renderer);

#endif /* Tilemap_h */
