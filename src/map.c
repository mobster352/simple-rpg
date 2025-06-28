#include "raylib.h"
#include "map.h"
#include "constants.h"
#include "stdlib.h"

Rectangle* buildColliders(int mapIndex);

Map* initMaps(){
    int numMaps = 1;
    Map* maps = malloc(sizeof(Map) * numMaps);
    maps[0].index = START_MAP;
    maps[0].texture = LoadTexture("maps/map.png");
    maps[0].colliders = buildColliders(START_MAP);
    return maps;
}

void DrawColliders(Rectangle* colliders, bool debug){
    if(debug){
        for(int i=0; i < 4; i++){
            DrawRectangleLines(colliders[i].x, colliders->y, colliders[i].width, colliders[i].height, RED);
        }
    }
}

void DrawMap(Map* maps, int index, bool debug){
    if(index == START_MAP){
        DrawTexture(maps[index].texture,0,0,WHITE);
        DrawColliders(maps[index].colliders, debug);
    }
}

void unloadMaps(Map* maps){
    for(int i=0; i<sizeof(maps); i++){
        UnloadTexture(maps[i].texture);
    }
    free(maps->colliders);
    free(maps);
}

Rectangle* buildColliders(int mapIndex){
    int numRecs = 4;
    Rectangle* recs = malloc(sizeof(Rectangle) * numRecs);
    if(mapIndex == START_MAP){
        Rectangle mapBorder = {
            0,
            0,
            GetScreenWidth(),
            GetScreenHeight()
        };
        recs[0] = mapBorder;
        Rectangle house1 = {
            255,
            23,
            140,
            180
        };
        recs[1] = house1;
    }
    return recs;
}