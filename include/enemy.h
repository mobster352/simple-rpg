#ifndef ENEMY_H
#define ENEMY_H

#include "transform2D.h"
#include "sprite.h"

typedef struct enemyPath {
    Vector2* points;
    int pointCount;
    int pointIndex;
    float waitTime;
    Vector2 movingToPoint;
    bool isMoving;
} EnemyPath;

typedef struct enemy {
    Transform2D transform2D;
    Sprite sprite;
    Rectangle hitbox;
    Rectangle attackHitbox;
    int hp;
    EnemyPath path;
} Enemy;

Enemy createEnemy(int xPos, int yPos, float width, float height, Animation idleAnimation, EnemyPath path);
void changeEnemySprite(Enemy* e, Sprite s);
Enemy* updateEnemy(Enemy* e);
void drawEnemy(Enemy* e, Animation* animations, bool debug);

#endif