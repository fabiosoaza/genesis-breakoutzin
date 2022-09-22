#include <genesis.h>
#include "utils.h"

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
    //-1 for negative, 1 for positive and 0 for 0
    return (x > 0) - (x < 0);
}

int Utils_randomInt(int min, int max)
{

    int rnd = random() % (max - min + 1) + min;
    return rnd;
}

Vect2D_f16 Utils_reflect(Vect2D_f16 vector, Vect2D_f16 normal)
{
    Vect2D_f16 result;
    fix16 val = fix16Mul(FIX16(2.0f), fix16Add( fix16Mul(vector.x, normal.x), fix16Mul(vector.y, normal.y)));
    result.x = fix16Sub(vector.x, fix16Mul(normal.x,val));
    result.y = fix16Sub(vector.y, fix16Mul(normal.y,val));
    return result;

          
}
