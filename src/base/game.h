#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"

void Game_setScene(Scene_init, Scene_update, Scene_draw, Scene_onInputEvent);
int Game_run(bool hardReset);


#endif //_GAME_H_