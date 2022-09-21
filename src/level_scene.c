#include <genesis.h>
#include <resources.h>
#include "configs.h"
#include "base/game_state.h"
#include "level_scene.h"
#include "hud.h"
#include "ball.h"
#include "paddle.h"

#include "brick.h"
#include "levels.h"
#include "sound_track.h"

static void _loadLevel(int level);
static void _checkEdgeCollision();
static void _checkPaddleCollision();
static void _checkBricksCollision();
static bool _checkBrickCollision(Ball *ball, Entity brick);
static void _checkLevelProgression();
static void _startGame();
static void _reset();
static void _winGame();
static void _endGame();
static void _pauseGame();
static void _drawWalls();
static void _playBrickSound(BlockType type);

#define CEILING_WIDTH_IN_TILE 40
#define CEILING_HEIGHT_IN_TILE 1
#define WALL_WIDTH_IN_TILE 1
#define WALL_HEIGHT_IN_TILE 28
#define WALL_POSITION_Y_IN_TILE 2
#define WALL_FOOTER_POSITION_IN_TILE 26

/*The edges of the play field*/

#define LEFT_EDGE 8 * WALL_WIDTH_IN_TILE
#define RIGHT_EDGE SCREEN_WIDTH - (WALL_WIDTH_IN_TILE * 8)
#define TOP_EDGE (WALL_POSITION_Y_IN_TILE + CEILING_HEIGHT_IN_TILE) * 8
#define BOTTOM_EDGE SCREEN_HEIGHT
#define DEFAULT_START_LEVEL 1

#define MAX_LEVEL 10
#define MAX_TRIES 5

int _score = 0;
int _tries = MAX_TRIES;
u8 _level = DEFAULT_START_LEVEL;
int _remainingBricks;

BrickWall _brickWall;
Ball _ball;
Paddle _paddle;

void LevelScene_init()
{

    VDP_loadTileSet(bgtile.tileset, TILE_USER_INDEX, DMA);
    PAL_setPalette(PAL1, bgtile.palette->data, DMA);

    /*Draw the texts*/
    VDP_setTextPlane(BG_A);

    // draw walls and ceiling
    _drawWalls();

    Hud_showStartMessage();

    _ball = Ball_create();
    Ball_loadSprite(&_ball);

    _paddle = Paddle_create();
    Paddle_loadSprite(&_paddle);
}
void LevelScene_update()
{
    if (GameState_isPlaying())
    {
        _checkEdgeCollision();
        _checkPaddleCollision();
        _checkBricksCollision();
        Ball_move(&_ball);
        Paddle_move(&_paddle, LEFT_EDGE, RIGHT_EDGE);
    }
}
void LevelScene_draw()
{
    Hud_showScore(_score);
    Hud_showTries(_tries);
    Hud_showLevel(_level);
    BrickWall_draw(&_brickWall);
    Ball_updateSprite(_ball);
    Paddle_updateSprite(_paddle);
    SPR_update();
}
void LevelScene_onInputEvent(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        /*Set player velocity if left or right are pressed;
         *set velocity to 0 if no direction is pressed */
        if (GameState_getState() == GAME_OVER || GameState_getState() == BEATED)
        {
            //
            if (state & BUTTON_START)
            {
                _reset();
            }
        }
        else if (GameState_getState() == RESTART_LEVEL || GameState_getState() == TITLE)
        {
            if (state & BUTTON_START)
            {
                _loadLevel(_level);
                _startGame();
            }
        }
        else if (GameState_isPlaying())
        {
            if (state & BUTTON_START)
            {
                _pauseGame();
            }
            else if (state & BUTTON_RIGHT)
            {
                Paddle_increaseVelocity(&_paddle);
            }
            else if (state & BUTTON_LEFT)
            {
                Paddle_decreaseVelocity(&_paddle);
            }
            else if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT))
            {
                Paddle_resetVelocity(&_paddle);
            }
        }
        else if (GameState_isPaused())
        {
            if (state & BUTTON_START)
            {
                _pauseGame();
            }
        }
    }
}

void LevelScene_setLevel(u8 level)
{
    if (level >= 0 && level <= MAX_LEVEL)
    {
        _level = level;
    }
    else
    {
        _level = DEFAULT_START_LEVEL;
    }
}

static void _loadLevel(int level)
{
    if (_brickWall.map != NULL)
    {
        BrickWall_clear(&_brickWall);
        Levels_destroy(_brickWall.map);
    }
    BrickMap *brickMap = Levels_loadLevel(level);
    _remainingBricks = Levels_totalBreakableBlocks(brickMap);
    _brickWall = BrickWall_create(brickMap, TOP_EDGE);
}

static void _checkEdgeCollision()
{
    bool collided = FALSE;

    if (Entity_getLeft(_ball.base) < LEFT_EDGE)
    {
        Entity_setX(&_ball.base, LEFT_EDGE);
        Ball_invertX(&_ball);
        collided = TRUE;
    }
    else if (Entity_getRight(_ball.base) > RIGHT_EDGE)
    {
        Entity_setX(&_ball.base, RIGHT_EDGE - _ball.base.width);
        Ball_invertX(&_ball);
        collided = TRUE;
    }

    if (Entity_getTop(_ball.base) < TOP_EDGE)
    {
        Entity_setY(&_ball.base, TOP_EDGE);
        Ball_invertY(&_ball);
        collided = TRUE;
    }
    else if (Entity_getBottom(_ball.base) > BOTTOM_EDGE)
    {
        if (_tries - 1 == 0)
        {
            _tries--;
            _endGame();
        }
        else
        {
            _tries--;
            _startGame();
        }
    }
    if (collided == TRUE)
    {
        Sound_playClip(SFX_WALL);
    }
}

static void _checkPaddleCollision()
{
    bool hit = Paddle_hitBallIfCollided(&_paddle, &_ball);

    if (hit == TRUE)
    {
        Sound_playClip(SFX_PADDLE);
        _ball.flashing = TRUE;
    }
}

static void _checkBricksCollision()
{
    if (Entity_collided(_ball.base, _brickWall.base))
    {

        for (int row = 0; row < _brickWall.map->rows; row++)
        {
            for (int col = 0; col < _brickWall.map->cols; col++)
            {
                if (_brickWall.map->map[row][col] != INVISIBLE)
                {
                    // creates a tem entity to checkCollision
                    Entity brick = (Entity){
                        .enabled = TRUE,
                        .x = _brickWall.base.x + (col * BRICK_WIDTH),
                        .y = _brickWall.base.y + (row * BRICK_HEIGHT),
                        .width = BRICK_WIDTH,
                        .height = BRICK_HEIGHT};
                    if (_checkBrickCollision(&_ball, brick))
                    {
                        _playBrickSound(_brickWall.map->map[row][col]);
                        if (_brickWall.map->map[row][col] != UNBREAKABLE)
                        {
                            _score += Brick_getScore((BlockType)_brickWall.map->map[row][col]);
                            _brickWall.map->map[row][col] = INVISIBLE;
                            _remainingBricks--;
                            _checkLevelProgression();
                        }
                    }
                }
            }
        }
    }
}

static bool _checkBrickCollision(Ball *ball, Entity brick)
{
    bool collided = FALSE;
    if (Entity_collided(ball->base, brick))
    {
        collided = TRUE;
        if (Entity_collidedFromRight(ball->base, brick))
        {
            Entity_setX(&ball->base, Entity_getRight(brick));
            Ball_invertX(ball);
        }
        else if (Entity_collidedFromLeft(ball->base, brick))
        {
            Entity_setX(&ball->base, Entity_getLeft(brick) - ball->base.width);
            Ball_invertX(ball);
        }
        else if (Entity_collidedFromBottom(ball->base, brick))
        {
            Entity_setY(&ball->base, Entity_getBottom(brick));
            Ball_invertY(ball);
        }
        else if (Entity_collidedFromTop(ball->base, brick))
        {
            Entity_setY(&ball->base, Entity_getTop(brick) - ball->base.height);
            Ball_invertY(ball);
        }
    }
    return collided;
}

static void _checkLevelProgression()
{

    if (_remainingBricks == 0)
    {
        if (_level + 1 == MAX_LEVEL)
        {
            _winGame();
            return;
        }
        else
        {
            _level++;
            GameState_changeState(RESTART_LEVEL);
            Hud_displayLevelMessage(_level);
        }
    }
}

static void _startGame()
{
    Hud_clearMessage();
    GameState_changeState(PLAYING);
    _brickWall.base.enabled = TRUE;
    Ball_reset(&_ball);
    Paddle_reset(&_paddle);
}

static void _reset()
{
    _tries = MAX_TRIES;
    _level = DEFAULT_START_LEVEL;
    _score = 0;
    _loadLevel(_level);
    _startGame();
}

static void _winGame()
{

    Hud_displayWinMessage();
    GameState_changeState(BEATED);
}

static void _endGame()
{
    GameState_gameOver();
    Hud_showGameOverMessage();
}

static void _pauseGame()
{
    GameState_pause();
    if (GameState_isPaused())
    {
        Hud_showPauseMessage();
    }
    else
    {
        Hud_clearMessage();
    }
}

static void _drawWalls()
{
    // ceiling
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 9), 0, WALL_POSITION_Y_IN_TILE, CEILING_WIDTH_IN_TILE, CEILING_HEIGHT_IN_TILE);
    // left wall
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 9), 0, WALL_POSITION_Y_IN_TILE, WALL_WIDTH_IN_TILE, WALL_HEIGHT_IN_TILE);
    // left footer
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, WALL_FOOTER_POSITION_IN_TILE, WALL_WIDTH_IN_TILE, 2);
    // right wall
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 9), 39, WALL_POSITION_Y_IN_TILE, WALL_WIDTH_IN_TILE, WALL_HEIGHT_IN_TILE);
    // right footer
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 10), 39, WALL_FOOTER_POSITION_IN_TILE, WALL_WIDTH_IN_TILE, 2);
}

void _playBrickSound(BlockType type)
{
    switch (type)
    {
    case RED:
        Sound_playClip(SFX_RED);
        break;
    case ORANGE:
        Sound_playClip(SFX_ORANGE);
        break;
    case GREEN:
        Sound_playClip(SFX_GREEN);
        break;
    case BLUE:
        Sound_playClip(SFX_BLUE);
        break;
    case UNBREAKABLE:
        Sound_playClip(SFX_WALL);
        break;
    case YELLOW_BRASILIS:
    case DARK_YELLOW:
        Sound_playClip(SFX_YELLOW);
        break;

    default:
        break;
    }
}