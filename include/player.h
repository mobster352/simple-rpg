#ifndef PLAYER_H
#define PLAYER_H

#include "transform2D.h"
#include "sprite.h"

typedef struct player {
    Transform2D transform2D;
    Sprite sprite;
} Player;

Player createPlayer(int xPos, int yPos);
void changeSprite(Player* p, Sprite s);
void drawPlayerHitbox(Player p);

#endif