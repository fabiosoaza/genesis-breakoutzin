#ifndef _UTILS_H_
#define _UTILS_H_

#include <genesis.h>

/*Draws text in the center of the screen*/
void Utils_showText(char s[])
{
    VDP_drawText(s, 20 - strlen(s) / 2, 15);
}

void Utils_showCenteredText(char s[], int posYInTiles)
{
    VDP_drawText(s, 20 - strlen(s) / 2, posYInTiles);
}

void Utils_resetScreen()
{
    if (SPR_isInitialized())
    {
        SPR_clear();
        SPR_reset();
        SPR_update();
        VDP_clearTextArea(0, 0, 320 / 8, 224 / 8);
    }
}

void Utils_showFormattedText(char *format, int posXInTiles, int posYInTiles, ...)
{
    va_list aptr;
    char buffer[100];
    int ret;
    va_start(aptr, posYInTiles);
    ret = vsprintf(buffer, format, aptr);
    va_end(aptr);
    VDP_drawText(buffer, posXInTiles, posYInTiles);
}

int Utils_sign(int x)
{
    return (x > 0) - (x < 0);
}

int Utils_randomInt(int min, int max)
{

    int rnd = random() % (max - min + 1) + min;
    return rnd;
}

#endif // _UTILS_H_