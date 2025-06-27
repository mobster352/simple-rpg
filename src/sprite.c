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

void PlayAnimation(Sprite* sprite, Animation* animations, int* index, float* animationTimer){
    // Update the animation timer
    *animationTimer += GetFrameTime();

    // Check if it's time to advance to the next frame
    if (*animationTimer >= ANIMATION_SPEED){
            //*index = (*index + 1) % sprite->animation.steps;
            *index += 1;
            *animationTimer = 0.0f;
    }

    sprite->source.x = getFrame(*index, sprite->animation.size);
    DrawTexturePro(sprite->animation.texture, sprite->source, sprite->dest, sprite->origin, sprite->rotation, sprite->tint);

    //if(*index==0){
    if(*index == sprite->animation.steps){
        if(sprite->animation.loop)        
            *index = 0;
        else {
            *index = 0;
            updateAnimation(sprite, animations[IDLE_ANIMATION]);
        }
    }        
}