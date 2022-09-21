#include "sound_track.h"
#include <resources.h>


#define SET_PCM(id, resource) \
    XGM_setPCM(id, resource, sizeof(resource))

#define PLAY_SFX(id) \
    (XGM_startPlayPCM(id, 2, SOUND_PCM_CH2))

void Sound_loadTracks()
{

    SET_PCM(SFX_BLUE, bluebeep);
    SET_PCM(SFX_GREEN, greenbeep);
    SET_PCM(SFX_ORANGE, orangebeep);
    SET_PCM(SFX_PADDLE, paddlebeep);
    SET_PCM(SFX_RED, redbeep);
    SET_PCM(SFX_WALL, wallbeep);
    SET_PCM(SFX_YELLOW, yellowbeep);
}

void Sound_playClip(u16 clip)
{
    switch (clip)
    {
    case SFX_BLUE:
        PLAY_SFX(SFX_BLUE);
        break;
    case SFX_GREEN:
        PLAY_SFX(SFX_GREEN);
        break;
    case SFX_ORANGE:
        PLAY_SFX(SFX_ORANGE);
        break;
    case SFX_PADDLE:
        PLAY_SFX(SFX_PADDLE);
        break;
    case SFX_RED:
        PLAY_SFX(SFX_RED);
        break;
    case SFX_YELLOW:
        PLAY_SFX(SFX_YELLOW);
        break;        
    case SFX_WALL:
        PLAY_SFX(SFX_WALL);
        break;
    default:
        break;
    }
}


#undef SET_PCM
#undef PLAY_SFX