typedef enum _GameState
{
    PAUSED,
    PLAYING,
    GAME_OVER,
    TITLE,
    BEATED,
    DEAD,
    RESTART_LEVEL
}GameState;

void GameState_changeState(GameState);
GameState GameState_getState();

bool GameState_isPlaying();
bool GameState_isPaused();
bool GameState_isGameOver();


void GameState_pause();
void GameState_gameOver();