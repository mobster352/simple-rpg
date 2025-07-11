#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PLAYER_SPEED 200
#define ANIMATION_SPEED 0.1f // 60 fps / need 10 fps for animation
#define ATTACK_DELAY 0.4f
#define ENEMY_SPEED 50.0f

enum ANIMATION {
    IDLE_ANIMATION,
    RUN_ANIMATION,
    ATTACK1_ANIMATION,
    ATTACK2_ANIMATION,
    GUARD_ANIMATION
};

enum MAPS {
    START_MAP
};

#endif