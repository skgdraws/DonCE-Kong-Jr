#include "player.h"
#include "game_state.h"
#include "network.h"
#include <SDL3/SDL.h>
#include <string.h>

// Instancia del jugador
static Player player = {
    .x = 100.0f,
    .y = 200.0f,
    .offsetX = 8.0f,
    .offsetY = 0.0f,
    .size = PLAYER_SIZE,
    .lives = 3,
    .score = 0,
    .spriteIndex = SPRITE_IDLE_1,
    .animCounter = 0,
    .facingRight = false  // Por defecto mira a la izquierda
};

Player* getPlayer(void) {
    return &player;
}

void updatePlayerFromServer(ServerPlayerData* serverData) {
    // Actualizar posicion directamente desde el servidor
    player.x = serverData->x - player.offsetX;
    player.y = serverData->y - player.offsetY;
    
    // Actualizar vidas y puntuacion
    player.lives = serverData->lives;
    player.score = serverData->score;
    
    // Actualizar direccion hacia la que mira
    if (serverData->facing != NULL) {
        player.facingRight = (strcmp(serverData->facing, "right") == 0);
    }
    
    // Verificar si las vidas llegaron a negativo (game over)
    if (player.lives < 0) {
        SDL_Log("Game Over! Lives: %d, Score: %d - Going to game over screen", player.lives, player.score);
        
        // Guardar el puntaje final
        finalScore = player.score;
        
        // Desconectar del servidor si estamos conectados
        if (isConnected()) {
            disconnectFromServer();
        }
        
        // Ir a la pantalla de game over
        gameState = GAME_STATE_GAME_OVER;
        
        // Resetear vidas para la próxima partida
        player.lives = 3;
        return;
    }
    
    // Determinar sprite base segun el estado del servidor
    int baseSprite;
    bool isMoving = false;
    bool isSingleFrame = false;  // Para estados que no tienen animacion de 2 frames
    
    if (strcmp(serverData->state, "walking") == 0) {
        baseSprite = SPRITE_WALK_1;
        isMoving = true;
    } else if (strcmp(serverData->state, "jumping") == 0) {
        baseSprite = SPRITE_JUMP;
        isMoving = false;
        isSingleFrame = true;
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
    if (isSingleFrame) {
        // Estados de un solo frame (salto)
        player.spriteIndex = baseSprite;
        player.animCounter = 0;
    } else if (isMoving) {
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
