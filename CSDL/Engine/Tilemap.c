//
//  Tilemap.c
//  CSDL
//
//  Created by Erik Morris on 7/23/24.
//

#include "Tilemap.h"

void Tile_init(Tile* tile, int xGridPos, int yGridPos, int spriteXId, int spriteYId, int tileSize, int mapHeight, float scale, double rotation, SDL_RendererFlip flip){
    tile->spriteXId=spriteXId;
    tile->spriteYId=spriteYId;
    tile->xGridPos=xGridPos;
    tile->yGridPos=yGridPos;
    tile->flip=flip;
    tile->rotation=rotation;
    tile->pos=(SDL_FRect){(xGridPos*tileSize*scale), -((yGridPos-mapHeight)*tileSize*scale), tileSize*scale, tileSize*scale};
}
void Tile_free(Tile* tile){
    
}
void Tilemap_init(Tilemap* tm, Texture* text, float scale, char* fileName, char* tileTypes, int numTileTypes){
    tm->tileTypesForParse = tileTypes;
    tm->numTileTypesForParse = numTileTypes;
    tm->spriteSheet=text;
    tm->scale = scale;
    Tilemap_populate(tm, fileName);
    tm->colliders = Tilemap_getColliders(tm);
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
    if (tm->colliders!=NULL){
        free(tm->colliders);
        tm->colliders=NULL;
    }
    if (tm->tileTypesForParse!=NULL)
    {
        tm->tileTypesForParse = NULL;
        tm->numTileTypesForParse = 0;
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
    printf("mapHeight: %d\nmapWidth: %d\nTotal bytes: %zu\n", tm->mapHeight,
           tm->mapWidth, totalBytesRead);

       fclose(file);
    
    int tileSize = TILE_SIZE;
    Tile* tiles = NULL;
    int capacity = 10;
    tiles = malloc(sizeof(Tile)*capacity);
    int tileAmount = 0;
    
    int spriteYId = 0; //Gets back tileId from the function call below
    int spriteXId = 0;
    for (int i = 0; i < totalBytesRead; i++)
    {
        char tile = content[i];
        
        if (Tilemap_isTileParseable(tm, tile, &spriteYId))//If a tile object
        {
            SDL_RendererFlip fl = SDL_FLIP_NONE;
            double angle = 0.0;
            bool tileLeft = false, tileUp = false, tileRight = false, tileDown = false;
            if (i!=0)//check for surrounding tiles
                if (content[i-1]==tile)
                    tileLeft = true;
            if (i-(tm->mapWidth) >= 0)
                if (content[i-tm->mapWidth] == tile)
                    tileUp=true;
            if (i!=totalBytesRead)
                if (content[i+1]==tile)
                    tileRight=true;
            if (i+tm->mapWidth<=totalBytesRead)
                if (content[i+tm->mapWidth]==tile)
                    tileDown=true;
            if (!(tileLeft || tileRight || tileUp || tileDown)) {spriteXId = 0;}
            else if (tileLeft && !(tileRight || tileUp || tileDown)){spriteXId = 4;}
            else if (tileRight && !(tileLeft || tileUp || tileDown)){spriteXId = 4; fl = SDL_FLIP_HORIZONTAL;}
            else if (tileUp && !(tileLeft || tileRight || tileDown)){spriteXId = 4; angle=90.0;}
            else if (tileDown && !(tileLeft || tileRight || tileUp)) {
                spriteXId = 4;
                angle = 90.0;
                fl = SDL_FLIP_HORIZONTAL;
            } else if (tileLeft && tileRight && !(tileUp || tileDown)) {
                spriteXId = 5;
            } else if (tileUp && tileDown && !(tileLeft || tileRight)) {
                spriteXId = 5;
                angle = 90.0;
            } else if (tileLeft && tileUp && !(tileRight || tileDown)) {
                spriteXId = 2;
                angle = 90.0;
            } else if (tileLeft && tileDown && !(tileRight || tileUp)) {
                spriteXId = 2;
            } else if (tileRight && tileUp && !(tileLeft || tileDown)) {
                spriteXId = 2;
                angle = 180.0;
                //fl = SDL_FLIP_HORIZONTAL;
            } else if (tileRight && tileDown && !(tileLeft || tileUp)) {
                spriteXId = 2;
                angle = 270.0;
                //fl = SDL_FLIP_HORIZONTAL;
            } else if (tileLeft && tileRight && tileUp && !tileDown) {
                spriteXId = 3;
                angle = 90.0;
            } else if (tileLeft && tileRight && tileDown && !tileUp) {
                spriteXId = 1;
                //angle = 270.0;
            } else if (tileUp && tileDown && tileLeft && !tileRight) {
                spriteXId = 3;
                //angle = 90.0;
            } else if (tileUp && tileDown && tileRight && !tileLeft) {
                spriteXId = 3;
                fl = SDL_FLIP_HORIZONTAL;
            } else if (tileLeft && tileRight && tileUp && tileDown) {
                spriteXId = 0; // Assuming a different sprite for all tiles present
            }
                     
            Tile_init(&tiles[tileAmount], i%tm->mapWidth, tm->mapHeight-(i/tm->mapWidth), spriteXId, spriteYId, tileSize, tm->mapHeight, tm->scale, angle, fl);
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
        SDL_FRect pos = tm->tiles[i].pos;
        pos.x = pos.x-xOffset; pos.y=pos.y-yOffset;
        Texture_render(tm->spriteSheet, renderer, &((SDL_Rect){tm->tiles[i].spriteXId*tilesize, tm->tiles[i].spriteYId*tilesize, tilesize, tilesize}), &pos, tm->tiles[i].rotation, NULL, tm->tiles[i].flip); //Fix how it renders tiles
    }
}

SDL_FRect* Tilemap_getColliders(Tilemap* tm){
    SDL_FRect* colliders = malloc(sizeof(SDL_FRect)*tm->tileAmount);
    if (colliders==NULL){
        perror("Could not allocate memory for colliders in tm");
        return NULL;
    }
    for (int i = 0; i<tm->tileAmount; i++){
        colliders[i]=tm->tiles[i].pos;
    }
    return colliders;
}

bool Tilemap_isTileParseable(Tilemap* tm, char tileToParse, int* tileId){
    *tileId = 0;
    for (int i = 0; i<tm->numTileTypesForParse; i++){
        if (tm->tileTypesForParse[i] == tileToParse)
            return true;
        *tileId=*tileId+1;
    }
    return false;
}

