#include <genesis.h>

#include "game.h"
#include "game_state.h"
#include "scene.h"

void Game_init();
void Game_update();
void Game_draw();
void Game_eventInputHandler(u16, u16, u16);

Scene_init _init;
Scene_update _update;
Scene_draw _draw;
Scene_onInputEvent _onInputEvent;

void Game_setScene(Scene_init init, Scene_update update, Scene_draw draw, Scene_onInputEvent onInputEvent)
{
    _init = init;
    _update = update;
    _draw = draw;
    _onInputEvent = onInputEvent;
}

int Game_run(bool hardReset)
{
    Game_init();

    while (TRUE)
    {
        Game_update();
        Game_draw();
        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}

void Game_init()
{
    JOY_init();
    JOY_setEventHandler(&Game_eventInputHandler);
    SPR_init();
    _init();
}
void Game_update()
{
    if (_update != NULL)
    {
        _update();
    }
}
void Game_draw()
{
    if (_draw != NULL)
    {
        _draw();
    }
}

void Game_eventInputHandler(u16 joy, u16 changed, u16 state)
{
    if (_onInputEvent != NULL)
    {
        _onInputEvent(joy, changed, state);
    }
}