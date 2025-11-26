#ifndef GAME_STATE_H
#define GAME_STATE_H

/**
 * @brief Estados posibles del juego
 */
typedef enum {
    GAME_STATE_MENU,       ///< Estado del menu principal
    GAME_STATE_SPECTATE,    ///< Estado del menu de espectacion
    GAME_STATE_CREDITS,    ///< Estado de pantalla de creditos
    GAME_STATE_CONNECTING, ///< Estado de conexion al servidor
    GAME_STATE_PLAYING,    ///< Estado de juego activo
    GAME_STATE_SPECTATING, ///< Estado de espectador
    GAME_STATE_QUIT        ///< Estado de salida del juego
} GameState;

/**
 * @brief Opciones disponibles en el menu principal
 */
typedef enum {
    MENU_START,    ///< Iniciar juego
    MENU_SPECTATE, ///< Espectar juego
    MENU_CREDITS,  ///< Creditos
    MENU_EXIT,     ///< Salir del juego
    MENU_COUNT     ///< Contador de opciones
} MenuOption;

/// Estado actual del juego
extern GameState gameState;

/// Opcion de menu actualmente seleccionada
extern MenuOption selectedOption;

#endif // GAME_STATE_H
