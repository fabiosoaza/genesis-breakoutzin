#include <genesis.h>
#include "hud.h"


const int SCORE_POS_X = 1;
const int SCORE_POS_Y = 1;
const int TRIES_POS_X = 14;
const int TRIES_POS_Y = 1;
const int LEVEL_POS_X = 27;
const int LEVEL_POS_Y = 1;
const int CENTRALIZED_MSG_POS_Y = 15;

#define MSG_START "PRESS START TO BEGIN!"
#define MSG_GAME_OVER "GAME OVER!"
#define MSG_PAUSE "PAUSE"
#define MSG_CONGRATULATIONS "CONGRATULATIONS YOU WIN!"
#define MSG_PLAY_AGAIN "PRESS START TO PLAY AGAIN!"
#define MSG_LEVEL "LEVEL %02d"

void Hud_show(char str[], int posXInTile, int posYInTile)
{
    VDP_clearText(posXInTile, posYInTile, strlen(str));
    VDP_drawText(str, posXInTile, posYInTile);
}

void Hud_showCentralized(char str[])
{
    Hud_clearMessage();
    VDP_drawText(str, abs(20 - strlen(str) / 2), CENTRALIZED_MSG_POS_Y);
}

void Hud_showScore(u16 score)
{
    char buffer[5];
    sprintf(buffer, "%03d", score);
    Hud_show(buffer, SCORE_POS_X, SCORE_POS_Y);
}

void Hud_showTries(u16 tries)
{
    char buffer[5];
    sprintf(buffer, "%d", tries);
    Hud_show(buffer, TRIES_POS_X, TRIES_POS_Y);
}

void Hud_showLevel(u16 level)
{
    char buffer[5];
    sprintf(buffer, "%d", level);
    Hud_show(buffer, LEVEL_POS_X, LEVEL_POS_Y);
}

void Hud_showStartMessage()
{
    Hud_showCentralized(MSG_START);
}

void Hud_showGameOverMessage()
{
    Hud_clearMessage();
    VDP_drawText(MSG_GAME_OVER, abs(20 - strlen(MSG_GAME_OVER) / 2), CENTRALIZED_MSG_POS_Y);
    VDP_drawText(MSG_PLAY_AGAIN, abs(20 - strlen(MSG_PLAY_AGAIN) / 2), CENTRALIZED_MSG_POS_Y + 1);

}

void Hud_showPauseMessage()
{
    Hud_showCentralized(MSG_PAUSE);
}

void Hud_displayWinMessage()
{
    Hud_clearMessage();
    VDP_drawText(MSG_CONGRATULATIONS, abs(20 - strlen(MSG_CONGRATULATIONS) / 2), CENTRALIZED_MSG_POS_Y);
    VDP_drawText(MSG_PLAY_AGAIN, abs(20 - strlen(MSG_PLAY_AGAIN) / 2), CENTRALIZED_MSG_POS_Y + 1);
}

void Hud_displayLevelMessage(u8 level)
{
    char msgLevel[10];
    Hud_clearMessage();
    sprintf(msgLevel, MSG_LEVEL, level);
    VDP_drawText(msgLevel, abs(20 - strlen(msgLevel) / 2), CENTRALIZED_MSG_POS_Y);
    VDP_drawText(MSG_START, abs(20 - strlen(MSG_START) / 2), CENTRALIZED_MSG_POS_Y + 1);
}

void Hud_clearMessage()
{
VDP_clearTextArea(0, CENTRALIZED_MSG_POS_Y, 40, 2);
}
