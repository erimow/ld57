//
//  Tilemap.c
//  CSDL
//
//  Created by Erik Morris on 7/23/24.
//

#include "Tilemap.h"

void Tile_init(Tile* tile, int xGridPos, int yGridPos, int spriteId){
    tile->spriteId=spriteId;
    tile->xGridPos=xGridPos;
    tile->yGridPos=yGridPos;
}
void Tile_free(Tile* tile){
    
}
void Tilemap_init(Tilemap* tm, Texture* text, char* fileName){
    tm->spriteSheet=text;
    Tilemap_populate(tm, fileName);
}
void Tilemap_free(Tilemap* tm){
    if (tm->tiles != NULL){
        free(tm->tiles);
        tm->tiles=NULL;
    }
    if (tm->spriteSheet!=NULL){
        Texture_free(tm->spriteSheet);
        tm->spriteSheet=NULL;
    }
    
}
void Tilemap_populate(Tilemap* tm, char* fileName){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
       }

       // Determine file size
       fseek(file, 0, SEEK_END);
       long fileSize = ftell(file);
       fseek(file, 0, SEEK_SET); // Reset file pointer to the beginning

       // Allocate memory for the file content
       char *content = (char*)malloc((fileSize + 1) * sizeof(char)); // +1 for null terminator
       if (content == NULL) {
           perror("Failed to allocate memory");
           fclose(file);
       }

       // Read file content
    int rows = 0;
       size_t totalBytesRead = 0;
       char line[1024];
       while (fgets(line, sizeof(line), file)) {
           size_t len = strlen(line);
           if (line[len - 1] == '\n') line[len - 1] = '\0'; // Remove newline character
           strcpy(content + totalBytesRead, line);
           rows++;
           totalBytesRead += len;
       }
       content[totalBytesRead] = '\0'; // Null-terminate the final string
        
    tm->mapHeight=rows;
    tm->mapWidth=(int)(totalBytesRead/rows);
    printf("mapHeight: %d\nmapWidth: %d\n", tm->mapHeight,
           tm->mapWidth);

       fclose(file);
    
    Tile* tiles = NULL;
    int capacity = 10;
    tiles = malloc(sizeof(Tile)*capacity);
    int tileAmount = 0;
    for (int i = 0; i < totalBytesRead+1; i++)
    {
        if (content[i]=='S')
        {
            Tile_init(&tiles[tileAmount], i%tm->mapWidth, tm->mapHeight-(i/tm->mapWidth), 4);
            printf("tile:%d->x:%d, y:%d\n", i, i%tm->mapWidth, tm->mapHeight-(i/tm->mapWidth));
            tileAmount++;
            if (tileAmount>=capacity){
                capacity*=2;
                Tile* newTiles = realloc(tiles, (sizeof(Tile)*tileAmount)*capacity);
                if (newTiles==NULL)
                {
                    printf("Could not allocate new memory to tiles in Tilemap_populate\n");
                    free(tiles);
                    free(content);
                    return;
                }
                tiles=newTiles;
            }
        }
    }
    Tile* newTiles = realloc(tiles, (sizeof(Tile)*tileAmount));
    if (newTiles==NULL)
    {
        printf("Could not allocate new memory to tiles in Tilemap_populate p.2\n");
        free(tiles);
        free(content);
        return;
    }
    tm->tiles=newTiles;
    tm->tileAmount=tileAmount;
    free(content);
}

void Tilemap_render(Tilemap* tm, SDL_Renderer* renderer, float xOffset, float yOffset){
    int tilesize = TILE_SIZE;
    for (int i = 0; i< tm->tileAmount; i++){
        Texture_render(tm->spriteSheet, renderer, &((SDL_Rect){tm->tiles[i].spriteId*tilesize, 0, tilesize, tilesize}), &((SDL_FRect){(tm->tiles[i].xGridPos*tilesize)-xOffset, -((tm->tiles[i].yGridPos-tm->mapHeight)*tilesize)-yOffset, tilesize, tilesize}), 0.0, NULL, SDL_FLIP_NONE);
    }
}
