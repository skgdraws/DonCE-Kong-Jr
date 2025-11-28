#include "game_state.h"

// Definicion de variables globales
GameState gameState = GAME_STATE_MENU;
MenuOption selectedOption = MENU_START;
SpectateOption selectedSpectateOption = SPECTATE_GAME_1;
int spectatingGameNumber = 1;
int finalScore = 0;
