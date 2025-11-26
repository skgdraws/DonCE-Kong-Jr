#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>

// Constantes de los enemigos
#define MAX_ENEMIES 10
#define ENEMY_SPEED 2.0f
#define ENEMY_SIZE 24.0f

// Estructura del enemigo
typedef struct {
    float x;
    float y;
    float velX;
    float velY;
    float speed;
    float size;
    bool active;
} Enemy;

// Funcion para generar un enemigo
void spawnEnemy(float x, float y, float velX, float velY);

// Funcion para actualizar enemigos
void updateEnemies(void);

// Obtener array de enemigos
Enemy* getEnemies(void);

// Obtener contador de enemigos
int getEnemyCount(void);

#endif // ENEMY_H
