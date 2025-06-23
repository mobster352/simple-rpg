#include "sprite.h"

Animation createAnimation(int id, Texture texture, int steps, int size){
    Animation a;
    a.id = id;
    a.texture = texture;
    a.steps = steps;
    a.size = size;
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
    return s;
}

void updateAnimation(Sprite* s, Animation animation){
    s->animation = animation;
}

int getFrame(int index, int spriteSize){
    return index * spriteSize;
}

void PlayAnimation(Sprite sprite, int* animation, int* index, bool* isOnceAnimationPlaying, float* animationTimer, float animationSpeed, bool loop){
    // Update the animation timer
    *animationTimer += GetFrameTime();

    // Check if it's time to advance to the next frame
    if (*animationTimer >= animationSpeed) {
            *index = (*index + 1) % sprite.animation.steps;
            *animationTimer = 0.0f;
    }

    sprite.source.x = getFrame(*index, sprite.animation.size);
    DrawTexturePro(sprite.animation.texture, sprite.source, sprite.dest, sprite.origin, sprite.rotation, sprite.tint);
    if(*index > sprite.animation.steps)
        if(loop)        
            *index = 0;
        else {
            *index = 0;
            *animation = 0;
            *isOnceAnimationPlaying = false;
        }
}

void changeAnimation(int* index, int* animation, int newAnimation){
    *index = 0;
    *animation = newAnimation;
}