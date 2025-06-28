#include "raylib.h"
#include "raymath.h"
#include "enemy.h"
#include "constants.h"
#include "stdio.h"

Enemy createEnemy(int xPos, int yPos, float width, float height, Animation idleAnimation){
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
    // Rectangle attackHitbox = {
    //     e->transform2D.position.x+120/e->sprite.animation.divisor, 
    //     e->transform2D.position.y+60/e->sprite.animation.divisor, 
    //     e->transform2D.width/5.0f, 
    //     e->transform2D.height/3.2f
    // };
    // e->attackHitbox = attackHitbox;
    // if(e->sprite.flipH)
    //     e->attackHitbox.x -= 90/e->sprite.animation.divisor;
}

void drawEnemyHitbox(Enemy e, bool debug){
    if(debug){
        DrawRectangleLines(e.hitbox.x, e.hitbox.y, e.hitbox.width, e.hitbox.height, RED);
        // DrawRectangleLines(p.attackHitbox.x, p.attackHitbox.y, p.attackHitbox.width, p.attackHitbox.height, RED);
    }
}

void moveEnemy(Enemy* e){
    // e->transform2D.position = Vector2Subtract(e->transform2D.position, (Vector2){10, 10});
    e->sprite.dest = (Rectangle){
        e->transform2D.position.x-100, 
        e->transform2D.position.y-100, 
        e->sprite.animation.size/e->sprite.animation.divisor, 
        e->sprite.animation.size/e->sprite.animation.divisor
    };
}

Enemy* updateEnemy(Enemy* e){
    moveEnemy(e);
    updateEnemyHitbox(e);
    return e;
}

void drawEnemy(Enemy e, bool debug){
    DrawTexturePro(e.sprite.animation.texture, e.sprite.source, e.sprite.dest, e.sprite.origin, e.sprite.rotation, e.sprite.tint);
    drawEnemyHitbox(e, debug);
}