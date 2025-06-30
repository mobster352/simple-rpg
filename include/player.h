#ifndef PLAYER_H
#define PLAYER_H

#include "transform2D.h"
#include "sprite.h"
#include "enemy.h"
#include "dynamic_array.h"

typedef struct player {
    Transform2D transform2D;
    Sprite sprite;
    float attackTimer;
    Rectangle hitbox;
    Rectangle attackHitbox;
} Player;

Player createPlayer(int xPos, int yPos, float width, float height, Animation idleAnimation);
void changeSprite(Player* p, Sprite s);
void changeAnimation(Player* p, Animation a);
void updatePlayer(Player* p, Animation* animations, DynamicArray* enemies);
void drawPlayer(Player* p, Animation* playerAnimations, bool* debug);

#endif