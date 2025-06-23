#include "raylib.h"
#include "player.h"

Player createPlayer(int xPos, int yPos){
    Player p;
    p.transform2D.position.x = xPos;
    p.transform2D.position.y = yPos;
    return p;
}

void changeSprite(Player* p, Sprite s){
    p->sprite = s;
}

void drawPlayerHitbox(Player p){
    DrawRectangleLines(p.sprite.dest.x, p.sprite.dest.y, p.sprite.source.width, p.sprite.source.height, RED);
}