#include <genesis.h>
#include <resources.h>
#include "base/game_state.h"
#include "base/utils.h"
#include "start_scene.h"
#include "level_scene.h"

typedef struct
{
    u16 x;
    u16 y;
    char label[10];
    bool selected;
} Option;

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
    {8, 17, "START", TRUE},
    {8, 18, "LEVEL %02d", FALSE}};

u8 currentMenuIndex = 0;
s8 levelToSelect = 1;

const u8 MAX_LEVELS = 10;

void StartScene_init()
{
    ballPositionX = START_POSITION_X;
    ballPositionY = START_POSITION_Y;
    ballVelX = START_VELOCITY_X;
    ballVelY = START_VELOCITY_Y;
    GameState_changeState(TITLE);
    Utils_showCenteredText("BREAKOUTZIN", 8);
    PAL_setPalette(PAL1, bgtile.palette->data, DMA);
    cursor = SPR_addSprite(&menucursor, 0, 0, 0);
    _updateCursorPosition();
    ballSprite = SPR_addSprite(&imgball, ballPositionX, ballPositionY, TILE_ATTR(PAL1, 1, FALSE, FALSE));
    defaultBallColor = PAL_getColor(22);
    ballColor = defaultBallColor;
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
        if (currentMenuIndex > 0)
        {
            currentMenuIndex--;
            _selectCurrentMenuOption();
            _updateCursorPosition();
        }
    }
    else if (changed & state & BUTTON_DOWN)
    {
        if (currentMenuIndex < NUM_OPTIONS - 1)
        {
            currentMenuIndex++;
            _selectCurrentMenuOption();
            _updateCursorPosition();
        }
    }
    else if (changed & state & BUTTON_LEFT)
    {
        if (options[1].selected)
        {
            _scrollLevel(-1);
        }
    }
    else if (changed & state & BUTTON_RIGHT)
    {
        if (options[1].selected)
        {
            _scrollLevel(+1);
        }
    }
        else if (changed & state & BUTTON_START)
    {
        if (options[0].selected)
        {
            _openGameScene();
        }
    }
}

void _openGameScene(){
    Utils_resetScreen();
    Game_setScene(LevelScene_init, LevelScene_update, LevelScene_draw, LevelScene_onInputEvent);
    //TODO refactor
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
    for (u8 i = 0; i < NUM_OPTIONS; i++)
    {
        Option o = options[i];
        // format level number
        if (i == NUM_OPTIONS - 1)
        {
            char levelLabel[9];
            sprintf(levelLabel, options[1].label, levelToSelect);
            VDP_drawText(levelLabel, o.x, o.y);
        }
        else
        {

            VDP_drawText(o.label, o.x, o.y);
        }
    }
}

void _scrollLevel(s8 levels)
{
    if ((levelToSelect + levels) > 0 && (levelToSelect + levels) <= MAX_LEVELS)
    {
        levelToSelect += levels;
    }
}

void _selectCurrentMenuOption()
{
    for (int i = 0; i < NUM_OPTIONS; i++)
    {
        options[i].selected = FALSE;
    }
    options[currentMenuIndex].selected = TRUE;
}

void _updateCursorPosition()
{
    SPR_setPosition(cursor, options[currentMenuIndex].x * 8 - 12, options[currentMenuIndex].y * 8);
}
