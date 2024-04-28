#include <genesis.h>
#include <resources.h>
#include "base/entity.h"
#include "paddle.h"
#include "ball.h"
#include "base/utils.h"

#define PADDLE_WIDTH 32
#define PADDLE_HEIGHT 8

#define PADDLE_POSITION_X 144
#define PADDLE_POSITION_Y 208

Paddle Paddle_create()
{
    Paddle paddle = {
        .sprite = NULL,
        .moving = FALSE,
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
    paddle->moving = FALSE;
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
    paddle->moving = TRUE;
}
void Paddle_decreaseVelocity(Paddle *paddle)
{
    paddle->base.velX = -3;
     paddle->moving = TRUE;
}

void Paddle_resetVelocity(Paddle *paddle)
{
    paddle->base.velX = 0;
     paddle->moving = FALSE;
}

bool Paddle_hitBallIfCollided(Paddle *paddle, Ball *ball)
{
    bool hit = FALSE;
    if (ball->base.x < Entity_getRight(paddle->base) && Entity_getRight(ball->base) > paddle->base.x)
    {
        if (ball->base.y < Entity_getBottom(paddle->base) && Entity_getBottom(ball->base) >= paddle->base.y)
        {

            hit = TRUE;

            bool hitLeftThird = ball->base.x < (paddle->base.x + paddle->base.width / 3);
            bool hitLeftPaddleEdge = hitLeftThird && ball->base.x < paddle->base.x;
            bool hitRightThird = ball->base.x > paddle->base.x + paddle->base.width - paddle->base.width / 3;
            bool hitRightPaddleEdge = hitRightThird && ball->base.x + ball->base.width > paddle->base.x + paddle->base.width;
            bool paddleCommingFromRight = paddle->moving = TRUE && paddle->base.x < paddle->base.oldX; 
            bool paddleCommingFromLeft = paddle->moving = TRUE && paddle->base.x > paddle->base.oldX;
            bool ballCommingFromRight = ball->base.x < ball->base.oldX; 
            bool ballCommingFromLeft = ball->base.x > ball->base.oldX;

            // decrement 1 pixel before invert ball to avoid multiple collisions
            Entity_setY(&ball->base, paddle->base.y - ball->base.height - 1);

            if (hitLeftThird)
            {
                ball->base.velX = -1;
            }
            else if (hitRightThird)
            {
                ball->base.velX = 1;
            }
            else
            {
                ball->base.velX = 0;
            }

            if( paddle->moving = TRUE &&( ballCommingFromLeft ^ paddleCommingFromLeft) ) {
                ball->base.velX += Utils_sign(ball->base.velX) * 3;
            }

            if( hitLeftPaddleEdge || hitRightPaddleEdge ) {
                ball->base.velX += Utils_sign(ball->base.velX) * 1;
            }
            

            Ball_invertY(ball);
        }
    }

    return hit;
}
