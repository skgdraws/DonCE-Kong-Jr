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

// Estructura de datos del servidor
typedef struct {
    float x;
    float y;
    const char* state;  // "idle", "walking", "climbing", etc.
} ServerPlayerData;

// Estructura del jugador
typedef struct {
    float x;
    float y;
    float size;
    int spriteIndex;
    int animCounter;
} Player;

// Funcion para actualizar jugador desde datos del servidor
void updatePlayerFromServer(ServerPlayerData* serverData);

// Obtener instancia del jugador
Player* getPlayer(void);

#endif // PLAYER_H
