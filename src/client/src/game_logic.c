#include "game_logic.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "network.h"
#include <SDL3/SDL.h>

static bool connectionAttempted = false;
static int connectingFrames = 0;

void update(void) {
    // Intentar conectar al servidor cuando estamos en estado CONNECTING
    if (gameState == GAME_STATE_CONNECTING) {
        connectingFrames++;
        
        // Esperar 2 frames para que se renderice la pantalla de conexion primero
        if (connectingFrames >= 2 && !connectionAttempted) {
            connectionAttempted = true;
            SDL_Log("Intentando conectar al servidor...");
            if (connectToServer("localhost", 2121)) {
                SDL_Log("Conectado exitosamente!");
                gameState = GAME_STATE_PLAYING;
            } else {
                SDL_Log("No se pudo conectar al servidor");
                gameState = GAME_STATE_MENU;
            }
            connectingFrames = 0;
            connectionAttempted = false;
        }
    } else {
        // Resetear contadores cuando salimos del estado CONNECTING
        connectingFrames = 0;
        connectionAttempted = false;
    }

    // Solo actualizar si estamos jugando
    if (gameState == GAME_STATE_PLAYING) {
        // TODO: Recibir datos del servidor
        // Por ahora, simulamos datos del servidor para testing local
        Player* player = getPlayer();
        ServerPlayerData serverData = {
            .x = player->x,  // Mantener posicion actual (sera reemplazado por datos del servidor)
            .y = player->y,
            .state = "idle"  // Estado por defecto (sera reemplazado por datos del servidor)
        };
        
        // Actualizar jugador con datos del servidor
        updatePlayerFromServer(&serverData);

        // TODO: Recibir datos de enemigos del servidor
        // Por ahora, simulamos sin enemigos (sera reemplazado por datos del servidor)
        ServerEnemyData serverEnemies[MAX_ENEMIES] = {0};
        updateEnemiesFromServer(serverEnemies, 0);
    }
}
