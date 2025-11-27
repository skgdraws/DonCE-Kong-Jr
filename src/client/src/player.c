#include "player.h"
#include <string.h>

// Instancia del jugador
static Player player = {
    .x = 100.0f,
    .y = 200.0f,
    .size = PLAYER_SIZE,
    .spriteIndex = SPRITE_IDLE_1,
    .animCounter = 0
};

Player* getPlayer(void) {
    return &player;
}

void updatePlayerFromServer(ServerPlayerData* serverData) {
    // Actualizar posicion directamente desde el servidor
    player.x = serverData->x;
    player.y = serverData->y;
    
    // Determinar sprite base segun el estado del servidor
    int baseSprite;
    bool isMoving = false;
    
    if (strcmp(serverData->state, "walking") == 0) {
        baseSprite = SPRITE_WALK_1;
        isMoving = true;
    } else if (strcmp(serverData->state, "climbing") == 0) {
        baseSprite = SPRITE_CLIMB_1;
        isMoving = true;
    } else if (strcmp(serverData->state, "idle") == 0) {
        baseSprite = SPRITE_IDLE_1;
        isMoving = false;
    } else {
        // Estado desconocido, usar idle por defecto
        baseSprite = SPRITE_IDLE_1;
        isMoving = false;
    }
    
    // Actualizar animacion
    if (isMoving) {
        player.animCounter++;
        if (player.animCounter >= ANIMATION_SPEED) {
            player.animCounter = 0;
            // Alternar entre frame 1 y 2
            if (player.spriteIndex == baseSprite) {
                player.spriteIndex = baseSprite + 1;
            } else {
                player.spriteIndex = baseSprite;
            }
        }
        // Si cambiamos de estado, resetear al primer frame
        if (player.spriteIndex < baseSprite || player.spriteIndex > baseSprite + 1) {
            player.spriteIndex = baseSprite;
            player.animCounter = 0;
        }
    } else {
        player.spriteIndex = baseSprite;
        player.animCounter = 0;
    }
}
