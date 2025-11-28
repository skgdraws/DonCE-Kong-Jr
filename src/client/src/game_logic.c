#include "game_logic.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "fruit.h"
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
    
    char buffer[4096];
    int copyLen = actualLength < sizeof(buffer) - 1 ? actualLength : sizeof(buffer) - 1;
    strncpy(buffer, actualData, copyLen);
    buffer[copyLen] = '\0';
    
    // Verificar que sea un mensaje STATE
    if (strncmp(buffer, "STATE|", 6) != 0) {
        SDL_Log("Invalid state message - not STATE");
        return;
    }
    
    // Buscar la seccion PLAYER usando strstr
    char* playerSection = strstr(buffer, "|PLAYER|");
    if (playerSection != NULL) {
        playerSection += 8; // Saltar "|PLAYER|"
        
        // Encontrar el fin de la seccion PLAYER (siguiente "|")
        char* playerEnd = strchr(playerSection, '|');
        if (playerEnd != NULL) {
            char playerData[256];
            int playerLen = playerEnd - playerSection;
            if (playerLen > 0 && playerLen < (int)sizeof(playerData)) {
                strncpy(playerData, playerSection, playerLen);
                playerData[playerLen] = '\0';
                
                float x, y;
                int lives, score;
                char state[32];
                char facing[32];
                int parsed = sscanf(playerData, "%f,%f,%d,%d,%31[^,],%31s", &x, &y, &lives, &score, state, facing);
                
                if (parsed >= 5) {
                    ServerPlayerData serverPlayer = {
                        .x = x,
                        .y = y,
                        .lives = lives,
                        .score = score,
                        .state = state,
                        .facing = (parsed >= 6) ? facing : "left"
                    };
                    updatePlayerFromServer(&serverPlayer);
                }
            }
        }
    }
    
    // Buscar la seccion ENEMIES usando strstr
    char* enemiesSection = strstr(buffer, "|ENEMIES|");
    if (enemiesSection != NULL) {
        enemiesSection += 9; // Saltar "|ENEMIES|"
        
        // Encontrar el fin de la seccion ENEMIES (siguiente "|")
        char* enemiesEnd = strchr(enemiesSection, '|');
        if (enemiesEnd != NULL) {
            char enemiesData[1024];
            int enemiesLen = enemiesEnd - enemiesSection;
            if (enemiesLen == 0) {
                // Lista de enemigos vacia - limpiar todos los enemigos
                ServerEnemyData emptyEnemies[1] = {0};
                updateEnemiesFromServer(emptyEnemies, 0);
            } else if (enemiesLen < (int)sizeof(enemiesData)) {
                strncpy(enemiesData, enemiesSection, enemiesLen);
                enemiesData[enemiesLen] = '\0';
                
                // Parsear lista de enemigos: redenemy(x,y);blueenemy(x,y);...
                ServerEnemyData serverEnemies[MAX_ENEMIES] = {0};
                int enemyCount = 0;
                
                char* ptr = enemiesData;
                while (*ptr != '\0' && enemyCount < MAX_ENEMIES) {
                    // Saltar espacios y separadores
                    while (*ptr == ';' || *ptr == ' ') ptr++;
                    if (*ptr == '\0') break;
                    
                    // Encontrar el parentesis de apertura
                    char* paren = strchr(ptr, '(');
                    if (paren == NULL) break;
                    
                    // Extraer el tipo (todo antes del parentesis)
                    char type[32] = {0};
                    int typeLen = paren - ptr;
                    if (typeLen > 0 && typeLen < (int)sizeof(type)) {
                        strncpy(type, ptr, typeLen);
                        type[typeLen] = '\0';
                        
                        // Parsear x,y,dir dentro de los parentesis (servidor envia floats y direccion)
                        float x, y;
                        char dir[16] = {0};
                        if (sscanf(paren, "(%f,%f,%15[^)])", &x, &y, dir) >= 2) {
                            serverEnemies[enemyCount].x = x;
                            serverEnemies[enemyCount].y = y;
                            serverEnemies[enemyCount].active = true;
                            serverEnemies[enemyCount].movingUp = (strcmp(dir, "up") == 0);
                            
                            // Determinar el tipo de enemigo
                            if (strstr(type, "red") != NULL) {
                                serverEnemies[enemyCount].type = ENEMY_TYPE_RED;
                            } else if (strstr(type, "blue") != NULL) {
                                serverEnemies[enemyCount].type = ENEMY_TYPE_BLUE;
                            } else {
                                serverEnemies[enemyCount].type = ENEMY_TYPE_RED;
                            }
                            
                            enemyCount++;
                        }
                    }
                    
                    // Avanzar al siguiente enemigo
                    char* nextSemi = strchr(ptr, ';');
                    if (nextSemi != NULL) {
                        ptr = nextSemi + 1;
                    } else {
                        break;
                    }
                }
                
                // Actualizar los enemigos
                updateEnemiesFromServer(serverEnemies, enemyCount);
            }
        }
    }
    
    // Buscar la seccion FRUITS usando strstr
    char* fruitsSection = strstr(buffer, "|FRUITS|");
    if (fruitsSection != NULL) {
        fruitsSection += 8; // Saltar "|FRUITS|"
        
        // Encontrar el fin de la seccion FRUITS (siguiente "|" o fin de cadena)
        char* fruitsEnd = strchr(fruitsSection, '|');
        int fruitsLen;
        if (fruitsEnd != NULL) {
            fruitsLen = fruitsEnd - fruitsSection;
        } else {
            fruitsLen = strlen(fruitsSection);
        }
        
        if (fruitsLen == 0) {
            // Lista de frutas vacia - limpiar todas las frutas
            ServerFruitData emptyFruits[1] = {0};
            updateFruitsFromServer(emptyFruits, 0);
        } else if (fruitsLen < 1024) {
            char fruitsData[1024];
            strncpy(fruitsData, fruitsSection, fruitsLen);
            fruitsData[fruitsLen] = '\0';
            
            // Parsear lista de frutas: orange(x,y);banana(x,y);strawberry(x,y);...
            ServerFruitData serverFruits[MAX_FRUITS] = {0};
            int fruitCount = 0;
            
            char* ptr = fruitsData;
            while (*ptr != '\0' && fruitCount < MAX_FRUITS) {
                // Saltar espacios y separadores
                while (*ptr == ';' || *ptr == ' ') ptr++;
                if (*ptr == '\0') break;
                
                // Encontrar el parentesis de apertura
                char* paren = strchr(ptr, '(');
                if (paren == NULL) break;
                
                // Extraer el tipo (todo antes del parentesis)
                char type[32] = {0};
                int typeLen = paren - ptr;
                if (typeLen > 0 && typeLen < (int)sizeof(type)) {
                    strncpy(type, ptr, typeLen);
                    type[typeLen] = '\0';
                    
                    // Parsear x,y dentro de los parentesis (servidor envia floats)
                    float x, y;
                    if (sscanf(paren, "(%f,%f)", &x, &y) == 2) {
                        serverFruits[fruitCount].x = x;
                        serverFruits[fruitCount].y = y;
                        serverFruits[fruitCount].active = true;
                        
                        // Determinar el tipo de fruta
                        if (strstr(type, "orange") != NULL) {
                            serverFruits[fruitCount].type = FRUIT_TYPE_ORANGE;
                        } else if (strstr(type, "banana") != NULL) {
                            serverFruits[fruitCount].type = FRUIT_TYPE_BANANA;
                        } else if (strstr(type, "strawberry") != NULL) {
                            serverFruits[fruitCount].type = FRUIT_TYPE_STRAWBERRY;
                        } else {
                            serverFruits[fruitCount].type = FRUIT_TYPE_ORANGE; // Default
                        }
                        
                        fruitCount++;
                    }
                }
                
                // Avanzar al siguiente fruta
                char* nextSemi = strchr(ptr, ';');
                if (nextSemi != NULL) {
                    ptr = nextSemi + 1;
                } else {
                    break;
                }
            }
            
            // Actualizar las frutas
            updateFruitsFromServer(serverFruits, fruitCount);
        }
    }
}

void update(void) {
    // Intentar conectar al servidor cuando estamos en estado CONNECTING (como jugador)
    if (gameState == GAME_STATE_CONNECTING) {
        connectingFrames++;
        
        // Esperar 2 frames para que se renderice la pantalla de conexion primero
        if (connectingFrames >= 2 && !connectionAttempted) {
            connectionAttempted = true;
            SDL_Log("Intentando conectar al servidor...");
            if (connectToServer("localhost", 2121)) {
                SDL_Log("Conectado exitosamente!");
                // Enviar comando de jugador al servidor
                sendCommandToServer("play");
                gameState = GAME_STATE_PLAYING;
            } else {
                SDL_Log("Fallo la conexion al servidor.");
                gameState = GAME_STATE_MENU;
            }
            connectingFrames = 0;
            connectionAttempted = false;
        }
    } 
    // Intentar conectar al servidor cuando estamos en estado CONNECTING_SPECTATE (como espectador)
    else if (gameState == GAME_STATE_CONNECTING_SPECTATE) {
        connectingFrames++;
        
        // Esperar 2 frames para que se renderice la pantalla de conexion primero
        if (connectingFrames >= 2 && !connectionAttempted) {
            connectionAttempted = true;
            SDL_Log("Intentando conectar como espectador al juego %d...", spectatingGameNumber);
            if (connectToServer("localhost", 2121)) {
                SDL_Log("Conectado como espectador!");
                // Enviar comando de espectador al servidor
                char spectateCmd[32];
                snprintf(spectateCmd, sizeof(spectateCmd), "spectate %d", spectatingGameNumber);
                sendCommandToServer(spectateCmd);
                gameState = GAME_STATE_SPECTATING;
            } else {
                SDL_Log("Fallo la conexion al servidor.");
                gameState = GAME_STATE_SPECTATE;
            }
            connectingFrames = 0;
            connectionAttempted = false;
        }
    } else {
        // Resetear contadores cuando salimos del estado CONNECTING
        connectingFrames = 0;
        connectionAttempted = false;
    }

    // Actualizar si estamos jugando o espectando
    if (gameState == GAME_STATE_PLAYING || gameState == GAME_STATE_SPECTATING) {
        // Recibir datos del servidor
        if (isConnected()) {
            char buffer[4096];
            int received = receiveFromServer(buffer, sizeof(buffer));
            
            if (received > 0) {
                // Parsear y actualizar estado del juego
                parseGameState(buffer, received);
            } else if (received == -1) {
                // Error de conexion
                SDL_Log("Conexion perdida con el servidor");
                gameState = GAME_STATE_MENU;
            }
            // received == 0 means no data available (non-blocking socket)
        }
    }
}
