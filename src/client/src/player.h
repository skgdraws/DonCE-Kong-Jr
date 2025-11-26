#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

// Constantes del jugador
#define PLAYER_SPEED 3.0f
#define PLAYER_SIZE 32.0f
#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 16
#define ANIMATION_SPEED 8

// Indices de sprites en el spritesheet
#define SPRITE_IDLE_1 1
#define SPRITE_WALK_1 2
#define SPRITE_WALK_2 3
#define SPRITE_CLIMB_1 7
#define SPRITE_CLIMB_2 8

/**
 * @brief Estructura con datos del jugador enviados por el servidor
 */
typedef struct {
    float x;              ///< Posicion X del jugador
    float y;              ///< Posicion Y del jugador
    const char* state;    ///< Estado del jugador ("idle", "walking", "climbing")
} ServerPlayerData;

/**
 * @brief Estructura que representa al jugador
 */
typedef struct {
    float x;            ///< Posicion X en pantalla
    float y;            ///< Posicion Y en pantalla
    float size;         ///< Tamaño para colisiones
    int spriteIndex;    ///< Indice del sprite actual
    int animCounter;    ///< Contador de frames de animacion
} Player;

/**
 * @brief Actualiza el jugador basado en datos recibidos del servidor
 * 
 * Esta funcion es la autoridad central para el estado del jugador.
 * Sincroniza posicion y animaciones con el servidor.
 * 
 * @param serverData Puntero a los datos del servidor
 */
void updatePlayerFromServer(ServerPlayerData* serverData);

/**
 * @brief Obtiene la instancia del jugador
 * @return Puntero a la estructura del jugador
 */
Player* getPlayer(void);

#endif // PLAYER_H
