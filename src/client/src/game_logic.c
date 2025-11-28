#include "game_logic.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "network.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool connectionAttempted = false;
static int connectingFrames = 0;

/**
 * @brief Parsea el estado del juego recibido del servidor
 * Formato: STATE|<gameNumber>|PLAYER|<x>,<y>,<lives>,<score>,<state>|ENEMIES|<enemyList>|FRUITS|<fruitList>
 */
static void parseGameState(const char* data, int dataLength) {
    // Java's writeUTF includes a 2-byte length prefix (big-endian)
    // Skip the first 2 bytes if they look like a UTF length prefix
    const char* actualData = data;
    int actualLength = dataLength;
    
    if (dataLength >= 2) {
        // Check if first 2 bytes are a length prefix
        unsigned char byte1 = (unsigned char)data[0];
        unsigned char byte2 = (unsigned char)data[1];
        unsigned short utfLength = (byte1 << 8) | byte2;
        
        // If the UTF length matches the remaining data length, skip the prefix
        if (utfLength == dataLength - 2) {
            actualData = data + 2;
            actualLength = utfLength;
        }
    }
    
    SDL_Log("Received game state (%d bytes): %.*s", actualLength, actualLength, actualData);
    
    char buffer[4096];
    int copyLen = actualLength < sizeof(buffer) - 1 ? actualLength : sizeof(buffer) - 1;
    strncpy(buffer, actualData, copyLen);
    buffer[copyLen] = '\0';
    
    // Tokenizar por separador '|'
    char* token = strtok(buffer, "|");
    
    // Verificar que sea un mensaje STATE
    if (token == NULL || strcmp(token, "STATE") != 0) {
        SDL_Log("Invalid state message - not STATE");
        return;
    }
    
    // Saltar gameNumber
    token = strtok(NULL, "|");
    if (token == NULL) {
        SDL_Log("No game number");
        return;
    }
    
    // Parsear datos del jugador
    token = strtok(NULL, "|");
    if (token != NULL && strcmp(token, "PLAYER") == 0) {
        token = strtok(NULL, "|");
        if (token != NULL) {
            float x, y;
            int lives, score;
            char state[32];
            int parsed = sscanf(token, "%f,%f,%d,%d,%31s", &x, &y, &lives, &score, state);
            SDL_Log("Parsed %d fields: x=%.1f, y=%.1f, lives=%d, score=%d, state=%s", 
                    parsed, x, y, lives, score, parsed == 5 ? state : "NONE");
            
            if (parsed == 5) {
                ServerPlayerData playerData = {
                    .x = x,
                    .y = y,
                    .lives = lives,
                    .score = score,
                    .state = state
                };
                updatePlayerFromServer(&playerData);
                SDL_Log("Player position updated to: %.1f, %.1f", x, y);
            } else {
                SDL_Log("Failed to parse player data (parsed %d/5 fields)", parsed);
            }
        }
    } else {
        SDL_Log("No PLAYER token found, got: %s", token ? token : "NULL");
    }
    
    // Parsear enemigos
    token = strtok(NULL, "|");
    if (token != NULL && strcmp(token, "ENEMIES") == 0) {
        token = strtok(NULL, "|");
        if (token != NULL && strlen(token) > 0) {
            // TODO: Parsear lista de enemigos
            // Formato: red(x,y);blue(x,y);...
        }
    }
    
    // Parsear frutas
    token = strtok(NULL, "|");
    if (token != NULL && strcmp(token, "FRUITS") == 0) {
        token = strtok(NULL, "|");
        if (token != NULL && strlen(token) > 0) {
            // TODO: Parsear lista de frutas
            // Formato: banana(x,y);orange(x,y);...
        }
    }
}

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
                SDL_Log("No se pudo conectar al servidor\\nJuego corre en modo debug.");
                gameState = GAME_STATE_PLAYING;
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
        // Recibir datos del servidor
        if (isConnected()) {
            char buffer[4096];
            int received = receiveFromServer(buffer, sizeof(buffer));
            
            if (received > 0) {
                SDL_Log("Received %d bytes from server", received);
                // Parsear y actualizar estado del juego
                parseGameState(buffer, received);
            } else if (received == -1) {
                // Error de conexion
                SDL_Log("Conexion perdida con el servidor");
                gameState = GAME_STATE_MENU;
            }
            // received == 0 means no data available (non-blocking socket)
        } else {
            SDL_Log("Not connected to server - running in debug mode");
            // Modo debug sin servidor - mantener posicion actual
            Player* player = getPlayer();
            ServerPlayerData serverData = {
                .x = player->x,
                .y = player->y,
                .lives = player->lives,
                .score = player->score,
                .state = "idle"
            };
            updatePlayerFromServer(&serverData);
        }

        // TODO: Actualizar enemigos con datos del servidor
        ServerEnemyData serverEnemies[MAX_ENEMIES] = {0};
        updateEnemiesFromServer(serverEnemies, 0);
    }
}
