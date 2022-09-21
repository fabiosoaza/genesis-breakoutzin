#ifndef _MENU_H_
#define _MENU_H_

#include <genesis.h>

typedef struct
{
    u16 x;
    u16 y;
    char label[10];
    bool selected;
    bool enabled;
} Option;

typedef struct
{
    u16 x;
    u16 y;
    bool enabled;
    int size;
    Option *options;
    u8 currentMenuIndex;
} Menu;

Menu Menu_create(Option *options, int size, int x, int y)
{
    Menu menu = (Menu){
        .x = x,
        .y = y,
        .enabled = FALSE,
        .size = size,
        .options = options,
        .currentMenuIndex = 0};
    return menu;
}

void Menu_increment(Menu *menu)
{
    if (menu->currentMenuIndex + 1 <= menu->size - 1)
    {
        menu->currentMenuIndex++;
        _selectCurrentOption(menu);
    }
}

void Menu_decrement(Menu *menu)
{
    if (menu->currentMenuIndex - 1 >= 0)
    {
        menu->currentMenuIndex--;
        _selectCurrentOption(menu);
    }
}

void _selectCurrentOption(Menu *menu)
{
    for (int i = 0; i < menu->size; i++)
    {
        menu->options[i].selected = FALSE;
    }
    menu->options[menu->currentMenuIndex].selected = TRUE;
}

#endif //_MENU_H_