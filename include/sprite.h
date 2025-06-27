#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct animation {
    int id;
    Texture texture;
    int steps;
    int size;
    float divisor;
    bool loop;
} Animation;

typedef struct sprite {
    Animation animation;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
    bool flipH;
} Sprite;

Animation createAnimation(int id, Texture texture, int steps, int size, float divisor, bool loop);
Sprite createSprite(Animation animation, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
void updateAnimation(Sprite* s, Animation animation);
void PlayAnimation(Sprite* sprite, Animation* animations, int* index, float* animationTimer);

#endif