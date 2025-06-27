#ifndef PLAYER_H
#define PLAYER_H

#include "transform2D.h"
#include "sprite.h"
#include "enemy.h"

typedef struct player {
    Transform2D transform2D;
    Sprite sprite;
    float attackTimer;
    Rectangle hitbox;
    Rectangle attackHitbox;
} Player;

Player createPlayer(int xPos, int yPos, float width, float height);
void changeSprite(Player* p, Sprite s);
void drawPlayerHitbox(Player p, bool* debug);
void changeAnimation(Player* p, Animation a, int* index);
void updatePlayer(Player* p, Animation* animations, int* index, Enemy* enemies, int enemiesLength);

#endif