#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <genesis.h>
#include <resources.h>
#include "base/entity.h"
#include "ball.h"

#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 8

#define PADDLE_POSITION_X 144
#define PADDLE_POSITION_Y 208

typedef struct _Paddle
{
    Entity base;
    Sprite *sprite;

} Paddle;

Paddle Paddle_create()
{
    Paddle paddle = {
        .sprite = NULL,
        .base = (Entity){
            .enabled = FALSE,
            .width = PADDLE_WIDTH,
            .height = PADDLE_HEIGHT,
            .velX = 0,
            .velY = 0,
            .x = PADDLE_POSITION_X,
            .y = PADDLE_POSITION_Y,
            .oldX = PADDLE_POSITION_X,
            .oldY = PADDLE_POSITION_Y

        }};
    return paddle;
}

void Paddle_reset(Paddle *paddle)
{
    paddle->base.enabled = TRUE;
    paddle->base.x = PADDLE_POSITION_X;
    paddle->base.y = PADDLE_POSITION_Y;
    paddle->base.oldX = PADDLE_POSITION_X;
    paddle->base.oldY = PADDLE_POSITION_Y;
    paddle->base.velX = 0;
    paddle->base.velY = 0;
}

void Paddle_loadSprite(Paddle *paddle)
{
    paddle->sprite = SPR_addSprite(&imgpaddle, paddle->base.x, paddle->base.y, TILE_ATTR(PAL1, 1, FALSE, FALSE));
}

void Paddle_updateSprite(Paddle paddle)
{
    if (!paddle.base.enabled)
    {
        SPR_setVisibility(paddle.sprite, HIDDEN);
    }
    else
    {
        SPR_setVisibility(paddle.sprite, VISIBLE);
        SPR_setPosition(paddle.sprite, paddle.base.x, paddle.base.y);
    }
}

void Paddle_move(Paddle *paddle, s16 leftEdge, s16 rightEdge)
{
    /*Add the player's velocity to its position*/
    paddle->base.x += paddle->base.velX;

    /*Keep the player within the bounds of the screen*/
    if (paddle->base.x < leftEdge)
        paddle->base.x = leftEdge;
    if (paddle->base.x + paddle->base.width > rightEdge)
        paddle->base.x = rightEdge - paddle->base.width;
}

void Paddle_increaseVelocity(Paddle *paddle)
{
    paddle->base.velX = 3;
}
void Paddle_decreaseVelocity(Paddle *paddle)
{
    paddle->base.velX = -3;
}

void Paddle_resetVelocity(Paddle *paddle)
{
    paddle->base.velX = 0;
}


bool Paddle_hitBallIfCollided(Paddle *paddle, Ball *ball)
{
    bool hit = FALSE;
    if (ball->base.x < Entity_getRight(paddle->base) && Entity_getRight(ball->base) > paddle->base.x)
    {
        if (ball->base.y < Entity_getBottom(paddle->base) && Entity_getBottom(ball->base) >= paddle->base.y)
        {
            //decrement 1 pixel before invert ball to avoid multiple collisions
            Entity_setY(&ball->base, paddle->base.y - ball->base.height - 1);
            // On collision, invert the velocity
            Ball_invertY(ball);

            hit = TRUE;
        }
    }
    
    return hit;
}

#endif //_PADDLE_H_