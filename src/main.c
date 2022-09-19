#include <genesis.h>
#include "base/game.h"
#include "start_scene.h"

int main(bool hardReset)
{
    Scene_init _init = StartScene_init;
    Scene_update _update = StartScene_update;
    Scene_draw _draw = StartScene_draw;
    Scene_onInputEvent _onInputEvent = StartScene_onInputEvent;

    Game_setScene(_init, _update, _draw, _onInputEvent);
    return Game_run(hardReset);

}
