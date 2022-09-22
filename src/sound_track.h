#ifndef _SOUND_BOX_H_
#define _SOUND_BOX_H_

#include <genesis.h>

#define SFX_BLUE 64
#define SFX_GREEN 65
#define SFX_ORANGE 66
#define SFX_PADDLE 67
#define SFX_RED 68
#define SFX_WALL 69
#define SFX_YELLOW 70

void Sound_loadTracks();
void Sound_playClip(u16 clip);

#endif //_SOUND_BOX_H_