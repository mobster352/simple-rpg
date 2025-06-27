#ifndef ENEMY_H
#define ENEMY_H

#include "transform2D.h"
#include "sprite.h"

typedef struct enemy {
    Transform2D transform2D;
    Sprite sprite;
    Rectangle hitbox;
    int hp;
} Enemy;

Enemy createEnemy(int xPos, int yPos, float width, float height);
void changeEnemySprite(Enemy* e, Sprite s);
void updateEnemy(Enemy* e);
void drawEnemy(Enemy e, bool debug);

#endif