#ifndef _BALL_H_
#define _BALL_H_

#include <genesis.h>
#include <resources.h>
#include "base/entity.h"

#define BALL_RADIUS 8
#define BALL_START_VEL 2
#define BALL_POSITION_X 154
#define BALL_POSITION_Y 112
#define BALL_MAX_VEL START_VEL * 10
#define BALL_FOREGROUND_COLOR_INDEX 22 

typedef struct _Ball
{
    Entity base;
    Sprite *sprite;
    u16 defaultColor;
    bool flashing;

} Ball;

static void _flash(Ball *ball);

static u8 _flashingFrameCounter = 0;

Ball Ball_create()
{
    Ball ball = {
        .defaultColor = PAL_getColor(BALL_FOREGROUND_COLOR_INDEX),
        .sprite = NULL,
        .flashing = FALSE,
        .base = (Entity){
            .enabled = FALSE,
            .width = BALL_RADIUS,
            .height = BALL_RADIUS,
            .velX = BALL_START_VEL,
            .velY = BALL_START_VEL,
            .x = BALL_POSITION_X,
            .y = BALL_POSITION_Y,
            .oldX = BALL_POSITION_X,
            .oldY = BALL_POSITION_Y

        }};
    return ball;
}

void Ball_reset(Ball *ball)
{
    // random() % (max - min + 1) + min
    int randomVx = (random() % (2 - 1 + 1)) + 1;

    ball->flashing = FALSE;
    ball->base.enabled = TRUE;
    ball->base.x = BALL_POSITION_X;
    ball->base.y = BALL_POSITION_Y;
    ball->base.oldX = BALL_POSITION_X;
    ball->base.oldY = BALL_POSITION_Y;
    ball->base.velX = randomVx == 2 ? -1 : 1;
    ball->base.velY = BALL_START_VEL;
}

void Ball_loadSprite(Ball *ball)
{
    ball->sprite = SPR_addSprite(&imgball, ball->base.x, ball->base.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
}

void Ball_updateSprite(Ball ball)
{
    if (!ball.base.enabled)
    {
        SPR_setVisibility(ball.sprite, HIDDEN);
    }
    else
    {
        SPR_setVisibility(ball.sprite, VISIBLE);
        SPR_setPosition(ball.sprite, ball.base.x, ball.base.y);
    }
}

void Ball_invertX(Ball *ball)
{
    ball->base.velX = -(ball->base.velX);
}

void Ball_invertY(Ball *ball)
{
    ball->base.velY = -(ball->base.velY);
}

void Ball_move(Ball *ball)
{
    // Position the ball
    Entity_setX(&ball->base, ball->base.x + ball->base.velX);
    Entity_setY(&ball->base, ball->base.y + ball->base.velY);
    _flash(ball);
}

static void _flash(Ball *ball)
{
    // Handle the flashing of the ball
    if (ball->flashing == TRUE)
    {
        // Cool flashing code goes here!
        _flashingFrameCounter++;
        if (_flashingFrameCounter % 4 == 0)
        {
            PAL_setColor(BALL_FOREGROUND_COLOR_INDEX, ball->defaultColor);
        }
        else if (_flashingFrameCounter % 2 == 0)
        {
            PAL_setColor(BALL_FOREGROUND_COLOR_INDEX, RGB24_TO_VDPCOLOR(0xffffff));
        }

        // Stop flashing
        if (_flashingFrameCounter > 30)
        {
            ball->flashing = FALSE;
            _flashingFrameCounter = 0;
            PAL_setColor(BALL_FOREGROUND_COLOR_INDEX, ball->defaultColor);
        }
    }
}

#endif //_BALL_H_