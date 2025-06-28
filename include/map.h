#include "raylib.h"
#ifndef MAP_H
#define MAP_H

typedef struct map {
    int index;
    Texture texture;
    Rectangle* colliders;
} Map;

Map* initMaps();
void DrawMap(Map* maps, int index, bool debug);
void unloadMaps(Map* maps);

#endif