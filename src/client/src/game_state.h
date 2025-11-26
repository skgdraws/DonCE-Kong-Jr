#ifndef GAME_STATE_H
#define GAME_STATE_H

// Estados del juego
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_QUIT
} GameState;

// Opciones del menu
typedef enum {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

// Variables globales de estado
extern GameState gameState;
extern MenuOption selectedOption;

#endif // GAME_STATE_H
