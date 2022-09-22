#ifndef _BALL_H_
#define _BALL_H_

#include <genesis.h>
#include "base/entity.h"

typedef struct _Ball
{
    Entity base;
    Sprite *sprite;
    u16 defaultColor;
    bool flashing;

} Ball;

Ball Ball_create();

void Ball_reset(Ball *ball);

void Ball_loadSprite(Ball *ball);

void Ball_updateSprite(Ball ball);

void Ball_invertX(Ball *ball);

void Ball_invertY(Ball *ball);

void Ball_move(Ball *ball);

void Ball_updateVelocity(Ball *ball, int vx, int vy);

#endif //_BALL_H_