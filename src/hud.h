#ifndef _HUD_H_
#define _HUD_H_

#include <genesis.h>

void Hud_show(char str[], int posXInTile, int posYInTile);
void Hud_showCentralized(char str[]);

void Hud_showScore(u16 score);

void Hud_showTries(u16 tries);

void Hud_showLevel(u16 level);
void Hud_showStartMessage();

void Hud_showGameOverMessage();

void Hud_showPauseMessage();
void Hud_displayWinMessage();
void Hud_displayLevelMessage(u8 level);

void Hud_clearMessage();

#endif //_HUD_H_