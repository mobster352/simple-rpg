#ifndef ENEMY_H
#define ENEMY_H

#include "transform2D.h"
#include "sprite.h"

typedef struct enemy {
    Transform2D transform2D;
    Sprite sprite;
    Rectangle hitbox;
    Rectangle attackHitbox;
    int hp;
} Enemy;

Enemy createEnemy(int xPos, int yPos, float width, float height, Animation idleAnimation);
void changeEnemySprite(Enemy* e, Sprite s);
Enemy* updateEnemy(Enemy* e);
void drawEnemy(Enemy* e, Animation* animations, bool debug);

#endif