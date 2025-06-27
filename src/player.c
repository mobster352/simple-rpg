#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "constants.h"
#include "stdio.h"

Player createPlayer(int xPos, int yPos, float width, float height){
    Player p;
    p.transform2D.position.x = xPos;
    p.transform2D.position.y = yPos;
    p.transform2D.width = width;
    p.transform2D.height = height;
    p.attackTimer = 0.0f;
    return p;
}

void changeSprite(Player* p, Sprite s){
    p->sprite = s;
}

Rectangle drawPlayerHitbox(Player p, bool* debug){
    Rectangle hitbox = {
        p.transform2D.position.x+70/p.sprite.animation.divisor, 
        p.transform2D.position.y+50/p.sprite.animation.divisor, 
        p.transform2D.width/4, 
        p.transform2D.height/2.5f
    };
    if(IsKeyPressed(KEY_F1))
        *debug = !*debug;
    if(*debug)
        DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED);
    return hitbox;
}

void changeAnimation(Player* p, Animation a, int* index){
    p->sprite.animation = a;
    *index = 0;
}

void movePlayer(Player* p, Animation* animations, Vector2 unitVector, int numKeysHeldDown){
    p->transform2D.position = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, PLAYER_SPEED/numKeysHeldDown * GetFrameTime()));
    p->sprite.dest = (Rectangle){
        p->transform2D.position.x, 
        p->transform2D.position.y, 
        p->sprite.animation.size/p->sprite.animation.divisor, 
        p->sprite.animation.size/p->sprite.animation.divisor
    };
}

void updateNumKeysHeldDown(int* numKeysHeldDown){
    if(*numKeysHeldDown >= 2)
        *numKeysHeldDown = 2;
    else
        *numKeysHeldDown += 1;
}

void updatePlayer(Player* p, Animation* animations, int* index){
    if(p->attackTimer > 0.0f)
        p->attackTimer -= GetFrameTime();
    if(IsKeyPressed(KEY_SPACE) && p->attackTimer <= 0.0f){
        p->attackTimer = ATTACK_DELAY;
        changeAnimation(p, animations[ATTACK1_ANIMATION], index);
        return;
    }
    if(p->attackTimer > 0.0f)
        return;

    int numKeysHeldDown = 0;
    if(IsKeyDown(KEY_D)){
        updateNumKeysHeldDown(&numKeysHeldDown);
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_A)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            if(p->sprite.flipH){
                p->sprite.source.width = -p->sprite.source.width;
                p->sprite.flipH = false;
            }
            movePlayer(p, animations, (Vector2){1,0}, numKeysHeldDown);
        }
    }
    if(IsKeyDown(KEY_A)){
        updateNumKeysHeldDown(&numKeysHeldDown);
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_D)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            if(!p->sprite.flipH){
                p->sprite.source.width = -p->sprite.source.width;
                p->sprite.flipH = true;
            }
            movePlayer(p, animations, (Vector2){-1,0}, numKeysHeldDown);
        }
    }
    if(IsKeyDown(KEY_W)){
        updateNumKeysHeldDown(&numKeysHeldDown);
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_S)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            movePlayer(p, animations, (Vector2){0,-1}, numKeysHeldDown);
        }
    }
    if(IsKeyDown(KEY_S)){
        updateNumKeysHeldDown(&numKeysHeldDown);
        if(numKeysHeldDown <= 2 && !IsKeyDown(KEY_W)){
            if(p->sprite.animation.id != RUN_ANIMATION){
                changeAnimation(p, animations[RUN_ANIMATION], index);
            }
            movePlayer(p, animations, (Vector2){0,1}, numKeysHeldDown);
        }
    }

    if(IsKeyReleased(KEY_D) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)){
        changeAnimation(p, animations[IDLE_ANIMATION], index);
    }
}