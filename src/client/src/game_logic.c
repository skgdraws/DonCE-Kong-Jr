#include "game_logic.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"

void update(void) {
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

        // Actualizar enemigos
        updateEnemies();
    }
}
