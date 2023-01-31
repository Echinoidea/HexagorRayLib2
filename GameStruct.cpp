#include <Game.cpp>

enum GameState {
    GS_INIT,
    GS_PLAYER1WIN,
    GS_PLAYER2WIN
};

struct GameStruct {
    HexGame game;
    
    GameState gameState;
};