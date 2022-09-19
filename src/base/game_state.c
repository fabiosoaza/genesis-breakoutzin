#include <genesis.h>
#include "game_state.h"

static GameState _state = TITLE;

void GameState_changeState(GameState newState)
{
    _state = newState;
}

GameState GameState_getState()
{
    return _state;
}

bool GameState_isPlaying()
{
    return _state == PLAYING;
}

bool GameState_isPaused()
{
    return _state == PAUSED;
}

bool GameState_isGameOver()
{
    return _state == GAME_OVER;
}

void GameState_pause()
{
    if (_state == PLAYING || _state == PAUSED)
    {
        _state = _state == PAUSED ? PLAYING : PAUSED;
    }
}

void GameState_gameOver()
{
    _state = GAME_OVER;
}
