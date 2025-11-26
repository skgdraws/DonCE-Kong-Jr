#include "enemy.h"
#include <SDL3/SDL.h>

// Array de enemigos
static Enemy enemies[MAX_ENEMIES] = {0};
static int enemyCount = 0;

Enemy* getEnemies(void) {
    return enemies;
}

int getEnemyCount(void) {
    return enemyCount;
}

void spawnEnemy(float x, float y, float velX, float velY) {
    // Buscar un slot libre en el array de enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].x = x;
            enemies[i].y = y;
            enemies[i].velX = velX;
            enemies[i].velY = velY;
            enemies[i].speed = ENEMY_SPEED;
            enemies[i].size = ENEMY_SIZE;
            enemies[i].active = true;
            enemyCount++;
            SDL_Log("Enemigo spawneado en (%.0f, %.0f)", x, y);
            return;
        }
    }
    SDL_Log("No se puede spawnear enemigo: maximo alcanzado");
}

void updateEnemiesFromServer(ServerEnemyData* serverEnemies, int count) {
    // Desactivar todos los enemigos primero
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
    }
    
    enemyCount = 0;
    
    // Actualizar con datos del servidor
    for (int i = 0; i < count && i < MAX_ENEMIES; i++) {
        if (serverEnemies[i].active) {
            enemies[i].x = serverEnemies[i].x;
            enemies[i].y = serverEnemies[i].y;
            enemies[i].size = ENEMY_SIZE;
            enemies[i].active = true;
            enemyCount++;
        }
    }
}
