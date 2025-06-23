#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct animation {
    int id;
    Texture texture;
    int steps;
    int size;
} Animation;

typedef struct sprite {
    Animation animation;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
} Sprite;

Animation createAnimation(int id, Texture texture, int steps, int size);
Sprite createSprite(Animation animation, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);
void updateAnimation(Sprite* s, Animation animation);
void PlayAnimation(Sprite sprite, int* animation, int* index, bool* isOnceAnimationPlaying, float* animationTimer, float animationSpeed, bool loop);
void changeAnimation(int* index, int* animation, int newAnimation);

#endif