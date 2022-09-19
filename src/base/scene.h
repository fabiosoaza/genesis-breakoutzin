#ifndef _SCENE_H_
#define _SCENE_H_

typedef void (*Scene_init)(void);
typedef void (*Scene_update)(void);
typedef void (*Scene_draw)(void);
typedef void (*Scene_onInputEvent)(u16, u16, u16);


#endif
