#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <genesis.h>
#include "base/entity.h"
#include "ball.h"

typedef struct _Paddle
{
    Entity base;
    Sprite *sprite;
    bool moving;

} Paddle;

Paddle Paddle_create();

void Paddle_reset(Paddle *paddle);

void Paddle_loadSprite(Paddle *paddle);

void Paddle_updateSprite(Paddle paddle);

void Paddle_move(Paddle *paddle, s16 leftEdge, s16 rightEdge);

void Paddle_increaseVelocity(Paddle *paddle);
void Paddle_decreaseVelocity(Paddle *paddle);

void Paddle_resetVelocity(Paddle *paddle);

bool Paddle_hitBallIfCollided(Paddle *paddle, Ball *ball);

#endif //_PADDLE_H_