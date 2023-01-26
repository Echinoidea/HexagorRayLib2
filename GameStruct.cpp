#include <Game.cpp>

enum GameState {
    GS_INIT,
    GS_ALIVE,
    GS_DEAD,
    GS_WON
};

struct GameStruct {
    HexGame game;
    
    GameState gameState;
};