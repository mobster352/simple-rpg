#ifndef PLAYER_H
#define PLAYER_H

#include "transform2D.h"
#include "sprite.h"

typedef struct player {
    Transform2D transform2D;
    Sprite sprite;
} Player;

Player createPlayer(int xPos, int yPos, float width, float height);
void changeSprite(Player* p, Sprite s);
Rectangle drawPlayerHitbox(Player p, bool* debug);
void changeAnimation(Player* p, Animation a);
void updatePlayer(Player* p, Animation* animations);

#endif