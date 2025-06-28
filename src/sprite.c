#include "stdio.h"

#include "sprite.h"
#include "constants.h"

Animation createAnimation(int id, Texture texture, int steps, int size, float divisor, bool loop){
    Animation a;
    a.id = id;
    a.texture = texture;
    a.steps = steps;
    a.size = size;
    a.divisor = divisor;
    a.loop = loop;
    a.timer = 0.0f;
    a.index = 0;
    return a;
}

Sprite createSprite(Animation animation, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint){
    Sprite s;
    s.animation = animation;
    s.source = source;
    s.dest = dest;
    s.origin = origin;
    s.rotation = rotation;
    s.tint = tint;
    s.flipH = false;
    return s;
}

void updateAnimation(Sprite* s, Animation animation){
    s->animation = animation;
}

int getFrame(int index, int spriteSize){
    return index * spriteSize;
}

void PlayAnimation(Sprite* sprite, Animation* animations){
    // Update the animation timer
    sprite->animation.timer += GetFrameTime();

    // Check if it's time to advance to the next frame
    if (sprite->animation.timer >= ANIMATION_SPEED){
            sprite->animation.index += 1;
            sprite->animation.timer = 0.0f;
    }

    sprite->source.x = getFrame(sprite->animation.index, sprite->animation.size);
    DrawTexturePro(sprite->animation.texture, sprite->source, sprite->dest, sprite->origin, sprite->rotation, sprite->tint);

    if(sprite->animation.index == sprite->animation.steps){
        if(sprite->animation.loop)        
            sprite->animation.index = 0;
        else {
            sprite->animation.index = 0;
            updateAnimation(sprite, animations[IDLE_ANIMATION]);
        }
    }        
}