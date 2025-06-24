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

void changeAnimation(Player* p, Animation a){
    p->sprite.animation = a;
}

void movePlayer(Player* p, Animation* animations){
    if(IsKeyDown(KEY_D)){
        if(p->sprite.animation.id != RUN_ANIMATION){
            changeAnimation(p, animations[RUN_ANIMATION]);
        }
        if(p->sprite.flipH){
            p->sprite.source.width = -p->sprite.source.width;
            p->sprite.flipH = false;
        }
        Vector2 unitVector = (Vector2){1,0};
        p->transform2D.position = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, PLAYER_SPEED * GetFrameTime()));
        p->sprite.dest = (Rectangle){
            p->transform2D.position.x, 
            p->transform2D.position.y, 
            p->sprite.animation.size/p->sprite.animation.divisor, 
            p->sprite.animation.size/p->sprite.animation.divisor
        };
    }
    if(IsKeyDown(KEY_A)){
        if(p->sprite.animation.id != RUN_ANIMATION){
            changeAnimation(p, animations[RUN_ANIMATION]);
        }
        if(!p->sprite.flipH){
            p->sprite.source.width = -p->sprite.source.width;
            p->sprite.flipH = true;
        }
        Vector2 unitVector = (Vector2){-1,0};
        p->transform2D.position = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, PLAYER_SPEED * GetFrameTime()));
        p->sprite.dest = (Rectangle){
            p->transform2D.position.x, 
            p->transform2D.position.y, 
            p->sprite.animation.size/p->sprite.animation.divisor, 
            p->sprite.animation.size/p->sprite.animation.divisor
        };
    }
    if(IsKeyDown(KEY_W)){
        if(p->sprite.animation.id != RUN_ANIMATION){
            changeAnimation(p, animations[RUN_ANIMATION]);
        }
        Vector2 unitVector = (Vector2){0,-1};
        p->transform2D.position = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, PLAYER_SPEED * GetFrameTime()));
        p->sprite.dest = (Rectangle){
            p->transform2D.position.x, 
            p->transform2D.position.y, 
            p->sprite.animation.size/p->sprite.animation.divisor, 
            p->sprite.animation.size/p->sprite.animation.divisor
        };
    }
    if(IsKeyDown(KEY_S)){
        if(p->sprite.animation.id != RUN_ANIMATION){
            changeAnimation(p, animations[RUN_ANIMATION]);
        }
        Vector2 unitVector = (Vector2){0,1};
        p->transform2D.position = Vector2Add(p->transform2D.position, Vector2Scale(unitVector, PLAYER_SPEED * GetFrameTime()));
        p->sprite.dest = (Rectangle){
            p->transform2D.position.x, 
            p->transform2D.position.y, 
            p->sprite.animation.size/p->sprite.animation.divisor, 
            p->sprite.animation.size/p->sprite.animation.divisor
        };
    }

    if(IsKeyReleased(KEY_D) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)){
        changeAnimation(p, animations[IDLE_ANIMATION]);
    }
}

void updatePlayer(Player* p, Animation* animations){
    movePlayer(p, animations);
}