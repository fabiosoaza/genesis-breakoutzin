#ifndef _LEVEL_SCENE_H_
#define _LEVEL_SCENE_H_

void LevelScene_init();
void LevelScene_update();
void LevelScene_draw();
void LevelScene_onInputEvent(u16, u16, u16);

void LevelScene_setLevel(u8 level);

#endif //_LEVEL_SCENE_H_