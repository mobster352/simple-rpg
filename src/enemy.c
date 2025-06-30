#include "raylib.h"
#include "raymath.h"
#include "enemy.h"
#include "constants.h"
#include "stdio.h"

Enemy createEnemy(int xPos, int yPos, float width, float height, Animation idleAnimation, EnemyPath path){
    Enemy e;
    e.transform2D.position.x = xPos;
    e.transform2D.position.y = yPos;
    e.transform2D.width = width;
    e.transform2D.height = height;
    e.hp = 1;

    Sprite enemySprite = createSprite(
		idleAnimation,
		(Rectangle){0,0,192,192},
		(Rectangle){
			e.transform2D.position.x, 
			e.transform2D.position.y, 
			idleAnimation.size/idleAnimation.divisor, 
			idleAnimation.size/idleAnimation.divisor, 
		},
		Vector2Zero(),
		0.0f,
		WHITE
	);
	changeEnemySprite(&e, enemySprite);
    e.path = path;

    return e;
}

void changeEnemySprite(Enemy* e, Sprite s){
    e->sprite = s;
}

void updateEnemyHitbox(Enemy* e){
    Rectangle hitbox = {
        e->transform2D.position.x-50/e->sprite.animation.divisor, 
        e->transform2D.position.y-70/e->sprite.animation.divisor, 
        e->transform2D.width/4, 
        e->transform2D.height/2.5f
    };
    e->hitbox = hitbox;
    Rectangle attackHitbox = {
        e->transform2D.position.x-2/e->sprite.animation.divisor, 
        e->transform2D.position.y-60/e->sprite.animation.divisor, 
        e->transform2D.width/5.0f, 
        e->transform2D.height/3.2f
    };
    e->attackHitbox = attackHitbox;
    if(e->sprite.flipH)
        e->attackHitbox.x -= 90/e->sprite.animation.divisor;
}

void drawEnemyHitbox(Enemy e, bool debug){
    if(debug){
        DrawRectangleLines(e.hitbox.x, e.hitbox.y, e.hitbox.width, e.hitbox.height, RED);
        DrawRectangleLines(e.attackHitbox.x, e.attackHitbox.y, e.attackHitbox.width, e.attackHitbox.height, RED);
    }
}

void moveEnemy(Enemy* e){
    if(!e->path.isMoving){
        if(e->path.waitTime <= 0.0f){
            if(e->path.pointIndex >= e->path.pointCount)
                e->path.pointIndex = 0;
            Vector2 point = e->path.points[e->path.pointIndex];
            Vector2 nextPos = Vector2Add(e->transform2D.position, point);
            e->transform2D.position = Vector2MoveTowards(e->transform2D.position,  nextPos, ENEMY_SPEED * GetFrameTime());
            e->sprite.dest = (Rectangle){
                e->transform2D.position.x-100, 
                e->transform2D.position.y-100, 
                e->sprite.animation.size/e->sprite.animation.divisor, 
                e->sprite.animation.size/e->sprite.animation.divisor
            };
            e->path.pointIndex += 1;
            e->path.movingToPoint = nextPos;
        }
        e->path.waitTime += GetFrameTime();
        if (e->path.waitTime >= 3.0f){
                e->path.waitTime = 0.0f;
                e->path.isMoving = true;
        }
    }
    else{
        e->transform2D.position = Vector2MoveTowards(e->transform2D.position,  e->path.movingToPoint, ENEMY_SPEED * GetFrameTime());
        e->sprite.dest = (Rectangle){
            e->transform2D.position.x-100, 
            e->transform2D.position.y-100, 
            e->sprite.animation.size/e->sprite.animation.divisor, 
            e->sprite.animation.size/e->sprite.animation.divisor
        };
        if(Vector2Distance(e->transform2D.position, e->path.movingToPoint) <= 0.1f)
            e->path.isMoving = false;
    }
}

Enemy* updateEnemy(Enemy* e){
    moveEnemy(e);
    updateEnemyHitbox(e);
    return e;
}

void drawEnemy(Enemy* e, Animation* animations, bool debug){
    // DrawTexturePro(e.sprite.animation.texture, e.sprite.source, e.sprite.dest, e.sprite.origin, e.sprite.rotation, e.sprite.tint);
    PlayAnimation(&e->sprite, animations);
    drawEnemyHitbox(*e, debug);
}