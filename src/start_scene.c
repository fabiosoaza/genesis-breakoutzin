#include <genesis.h>
#include <resources.h>
#include "base/game_state.h"
#include "base/utils.h"
#include "start_scene.h"
#include "level_scene.h"
#include "menu.h"
#include "sound_track.h"

Sprite *ballSprite;
Sprite *cursor;

const int START_POSITION_X = 100;
const int START_POSITION_Y = 100;
const int START_VELOCITY_X = 1;
const int START_VELOCITY_Y = 1;

/*The edges of the play field*/
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const TOP_EDGE = 0;
const BOTTOM_EDGE = 224;

int ballPositionX;
int ballPositionY;
int ballVelX;
int ballVelY;
int ballRadius = 8;

int flashing = FALSE;
int frameCounter = 0;

int defaultBallColor = 0;
int ballColor = 0;

#define NUM_OPTIONS 2
Option options[NUM_OPTIONS] = {
    (Option){.x = 8, .y = 17, .label = "START", .selected = TRUE, .enabled = TRUE},
    (Option){.x = 8, .y = 18, .label = "LEVEL %02d", .selected = FALSE, .enabled = TRUE}};

Menu menu;

const u8 MIN_LEVEL = 1;
const u8 MAX_LEVELS = 10;

s8 levelToSelect;

void StartScene_init()
{
    levelToSelect = MIN_LEVEL;
    Sound_loadTracks();
    ballPositionX = START_POSITION_X;
    ballPositionY = START_POSITION_Y;
    ballVelX = START_VELOCITY_X;
    ballVelY = START_VELOCITY_Y;
    GameState_changeState(TITLE);
    Utils_showCenteredText("BREAKOUTZIN", 8);
    PAL_setPalette(PAL1, bgtile.palette->data, DMA);
    cursor = SPR_addSprite(&menucursor, 0, 0, 0);
    ballSprite = SPR_addSprite(&imgball, ballPositionX, ballPositionY, TILE_ATTR(PAL1, 1, FALSE, FALSE));
    defaultBallColor = PAL_getColor(22);
    ballColor = defaultBallColor;
    menu = Menu_create(&options, NUM_OPTIONS, 8, 17);
    //menu.enabled = TRUE;
    _updateCursorPosition();
}

void StartScene_update()
{
    _checkEdgesCollision();
    _updateFlashEffect();
    // Position the ball
    ballPositionX += ballVelX;
    ballPositionY += ballVelY;
}

void StartScene_draw()
{
    _drawMenu();
    SPR_setPosition(ballSprite, ballPositionX, ballPositionY);
    PAL_setColor(22, ballColor);
    SPR_update();
}

void StartScene_onInputEvent(u16 joy, u16 changed, u16 state)
{
    if (changed & state & BUTTON_UP)
    {
        if (menu.enabled)
        {
            Menu_decrement(&menu);
            _updateCursorPosition();
        }
    }
    else if (changed & state & BUTTON_DOWN)
    {
        if (menu.enabled)
        {
            Menu_increment(&menu);
            _updateCursorPosition();
        }
    }
    else if (changed & state & BUTTON_LEFT)
    {
        if (menu.enabled && menu.options[1].selected)
        {
            _scrollLevel(-1);
        }
    }
    else if (changed & state & BUTTON_RIGHT)
    {
        if (menu.enabled && menu.options[1].selected)
        {
            _scrollLevel(+1);
        }
    }
    else if (changed & state & BUTTON_START)
    {

        _openGameScene();
    }
    // cheat to open level menu A+B+C+V
    else if (menu.enabled == FALSE && (state & BUTTON_A) && (state & BUTTON_B) && (state & BUTTON_C) && (state & BUTTON_DOWN))
    {

        menu.enabled = TRUE;
        _updateCursorPosition();
    }
}

void _openGameScene()
{
    Utils_resetScreen();
    Game_setScene(LevelScene_init, LevelScene_update, LevelScene_draw, LevelScene_onInputEvent);
    // TODO refactor
    LevelScene_setLevel(levelToSelect);
    LevelScene_init();
}

void _checkEdgesCollision()
{
    // Check horizontal bounds
    if (ballPositionX < LEFT_EDGE)
    {
        ballPositionX = LEFT_EDGE;
        ballVelX = -(ballVelX);
        flashing = TRUE;
    }
    else if (ballPositionX + ballRadius > RIGHT_EDGE)
    {
        ballPositionX = RIGHT_EDGE - ballRadius;
        ballVelX = -(ballVelX);
        flashing = TRUE;
    }

    // Check vertical bounds
    if (ballPositionY < TOP_EDGE)
    {
        ballPositionY = TOP_EDGE;
        ballVelY = -(ballVelY);
        flashing = TRUE;
    }
    else if (ballPositionY + ballRadius > BOTTOM_EDGE)
    {
        ballPositionY = BOTTOM_EDGE - ballRadius;
        ballVelY = -(ballVelY);
        flashing = TRUE;
    }
}

void _updateFlashEffect()
{
    // Handle the flashing of the ball
    if (flashing == TRUE)
    {
        // Cool flashing code goes here!
        frameCounter++;
        if (frameCounter % 4 == 0)
        {
            ballColor = defaultBallColor;
        }
        else if (frameCounter % 2 == 0)
        {
            ballColor = RGB24_TO_VDPCOLOR(0xffffff);
        }

        // Stop flashing
        if (frameCounter > 30)
        {
            flashing = FALSE;
            frameCounter = 0;
            ballColor = defaultBallColor;
        }
    }
}

void _drawMenu()
{
    if (menu.enabled == TRUE)
    {
        for (u8 i = 0; i < menu.size; i++)
        {

            // format level number
            if (i == menu.size - 1)
            {
                char levelLabel[9];
                sprintf(levelLabel, menu.options[i].label, levelToSelect);
                VDP_drawText(levelLabel, menu.options[i].x, menu.options[i].y);
            }
            else
            {

                VDP_drawText(menu.options[i].label, menu.options[i].x, menu.options[i].y);
            }
        }
    }
    else
    {
        VDP_drawText(menu.options[0].label, menu.options[0].x, menu.options[0].y);
    }
}

void _scrollLevel(s8 levels)
{
    if ((levelToSelect + levels) >= MIN_LEVEL && (levelToSelect + levels) <= MAX_LEVELS)
    {
        levelToSelect += levels;
    }
}

void _updateCursorPosition()
{
    if (menu.enabled)
    {
        SPR_setPosition(cursor, menu.options[menu.currentMenuIndex].x * 8 - 12, menu.options[menu.currentMenuIndex].y * 8);
        SPR_setVisibility(cursor, VISIBLE);
    }
    else
    {
        SPR_setVisibility(cursor, HIDDEN);
    }
}
