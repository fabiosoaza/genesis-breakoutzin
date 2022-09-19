typedef enum _GameState
{
    PAUSED,
    PLAYING,
    GAME_OVER,
    TITLE,
    BEATED
}GameState;

void GameState_changeState(GameState);
GameState GameState_getState();

bool GameState_isPlaying();
bool GameState_isPaused();
bool GameState_isGameOver();


void GameState_pause();
void GameState_gameOver();