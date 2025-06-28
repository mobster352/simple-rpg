#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "constants.h"
#include "stdio.h"
#include "enemy.h"
#include "dynamic_array.h"

Player createPlayer(int xPos, int yPos, float width, float height, Animation idleAnimation){
    Player p;
    p.transform2D.position.x = xPos;
    p.transform2D.position.y = yPos;
    p.transform2D.width = width;
    p.transform2D.height = height;
    p.attackTimer = 0.0f;

    Sprite playerSprite = createSprite(
		idleAnimation,
		(Rectangle){0,0,192,192},
		(Rectangle){
			p.transform2D.position.x, 
			p.transform2D.position.y, 
			idleAnimation.size/idleAnimation.divisor, 
			idleAnimation.size/idleAnimation.divisor, 
		},
		Vector2Zero(),
		0.0f,
		WHITE
	);
	changeSprite(&p, playerSprite);

    return p;
}

void changeSprite(Player* p, Sprite s){
    p->sprite = s;
}

void updatePlayerHitbox(Player* p){
    Rectangle hitbox = {
        p->transform2D.position.x+70/p->sprite.animation.divisor, 
        p->transform2D.position.y+50/p->sprite.animation.divisor, 
        p->transform2D.width/4, 
        p->transform2D.height/2.5f
    };
    p->hitbox = hitbox;
    Rectangle attackHitbox = {
        p->transform2D.position.x+120/p->sprite.animation.divisor, 
        p->transform2D.position.y+60/p->sprite.animation.divisor, 
        p->transform2D.width/5.0f, 
        p->transform2D.height/3.2f
    };
    p->attackHitbox = attackHitbox;
    if(p->sprite.flipH)
        p->attackHitbox.x -= 90/p->sprite.animation.divisor;
}

void drawPlayerHitbox(Player p, bool* debug){
    if(IsKeyPressed(KEY_F1))
        *debug = !*debug;
    if(*debug){
        DrawRectangleLines(p.hitbox.x, p.hitbox.y, p.hitbox.width, p.hitbox.height, RED);
        DrawRectangleLines(p.attackHitbox.x, p.attackHitbox.y, p.attackHitbox.width, p.attackHitbox.height, RED);
    }
}

void changeAnimation(Player* p, Animation a, int* index){
    p->sprite.animation = a;
    *index = 0;
}

bool checkCollisionsWithEnemies(Player p, DynamicArray* enemies){
    for(int i=0; i<enemies->size; i++){
        Enemy* e = (Enemy*) da_get(enemies, i);
        if(CheckCollisionRecs(p.hitbox, e->hitbox)){
            return true;
        }
    }
    return false;
}

Enemy* hitEnemy(Player p, DynamicArray* enemies){
    for(int i=0; i<enemies->size; i++){
        Enemy* e = (Enemy*) da_get(enemies, i);
        if(CheckCollisionRecs(p.attackHitbox, e->hitbox)){
            return e;
        }
    }
    return NULL;
}

void movePlayer(Player* p, Animation* animations, Vector2 unitVector, int numKeysHeldDown, DynamicArray* enemies){
    int speed;
    if(numKeysHeldDown >= 2){
        speed = PLAYER_SPEED - PLAYER_SPEED/4;
    }
    else{
        speed = PLAYER_SPEED;
    }
    // Simulate the new position
    Vector2 newPosition = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, speed * GetFrameTime()));

    // Create a temporary player with the new position and updated hitbox
    Player tempPlayer = *p;
    tempPlayer.transform2D.position = newPosition;
    updatePlayerHitbox(&tempPlayer);

    // Only move if no collision at the new position
    if(!checkCollisionsWithEnemies(tempPlayer, enemies)){
        p->transform2D.position = newPosition;
    }

    p->sprite.dest = (Rectangle){
        p->transform2D.position.x, 
        p->transform2D.position.y, 
        p->sprite.animation.size/p->sprite.animation.divisor, 
        p->sprite.animation.size/p->sprite.animation.divisor
    };
}

void updateNumKeysHeldDown(int* numKeysHeldDown){
    *numKeysHeldDown += 1;
}

void updatePlayer(Player* p, Animation* animations, int* index, DynamicArray* enemies){
    if(p->attackTimer > 0.0f)
        p->attackTimer -= GetFrameTime();
    if(IsKeyPressed(KEY_SPACE) && p->attackTimer <= 0.0f){
        p->attackTimer = ATTACK_DELAY;
        changeAnimation(p, animations[ATTACK1_ANIMATION], index);

        Enemy* hit = hitEnemy(*p, enemies);
        if(hit != NULL){
            hit->hp -= 1;
        }
        return;
    }
    if(p->attackTimer > 0.0f)
        return;

    int numKeysHeldDown = 0;
    if(IsKeyDown(KEY_D))
        updateNumKeysHeldDown(&numKeysHeldDown);
    if(IsKeyDown(KEY_A))
        updateNumKeysHeldDown(&numKeysHeldDown);
    if(IsKeyDown(KEY_W))
        updateNumKeysHeldDown(&numKeysHeldDown);
    if(IsKeyDown(KEY_S))
        updateNumKeysHeldDown(&numKeysHeldDown);
    
    if(IsKeyDown(KEY_D)){
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_A)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            if(p->sprite.flipH){
                p->sprite.source.width = -p->sprite.source.width;
                p->sprite.flipH = false;
            }
            movePlayer(p, animations, (Vector2){1,0}, numKeysHeldDown, enemies);
        }
        else
            if(p->sprite.animation.id != IDLE_ANIMATION)
                changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
    if(IsKeyDown(KEY_A)){
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_D)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            if(!p->sprite.flipH){
                p->sprite.source.width = -p->sprite.source.width;
                p->sprite.flipH = true;
            }
            movePlayer(p, animations, (Vector2){-1,0}, numKeysHeldDown, enemies);
        }
        else
            if(p->sprite.animation.id != IDLE_ANIMATION)
                changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
    if(IsKeyDown(KEY_W)){
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_S)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            movePlayer(p, animations, (Vector2){0,-1}, numKeysHeldDown, enemies);
        }
        else
            if(p->sprite.animation.id != IDLE_ANIMATION)
                changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
    if(IsKeyDown(KEY_S)){
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_W)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            movePlayer(p, animations, (Vector2){0,1}, numKeysHeldDown, enemies);
        }
        else
            if(p->sprite.animation.id != IDLE_ANIMATION)
                changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
    updatePlayerHitbox(p);
    if((IsKeyReleased(KEY_D) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)) && p->sprite.animation.id != IDLE_ANIMATION){
        changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
}