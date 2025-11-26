#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>

// Constantes de los enemigos
#define MAX_ENEMIES 10
#define ENEMY_SPEED 2.0f
#define ENEMY_SIZE 24.0f

/**
 * @brief Estructura que representa un enemigo en el juego
 */
typedef struct {
    float x;        ///< Posicion X del enemigo
    float y;        ///< Posicion Y del enemigo
    float velX;     ///< Velocidad horizontal
    float velY;     ///< Velocidad vertical
    float speed;    ///< Velocidad base del enemigo
    float size;     ///< Tamaño del enemigo para colisiones
    bool active;    ///< Estado de activacion del enemigo
} Enemy;

/**
 * @brief Estructura de datos de enemigo recibida del servidor
 */
typedef struct {
    float x;        ///< Posicion X del enemigo
    float y;        ///< Posicion Y del enemigo
    int id;         ///< Identificador unico del enemigo
    bool active;    ///< Estado de activacion del enemigo
} ServerEnemyData;

/**
 * @brief Genera un nuevo enemigo en la posicion especificada
 * @param x Posicion inicial X
 * @param y Posicion inicial Y
 * @param velX Velocidad horizontal inicial
 * @param velY Velocidad vertical inicial
 */
void spawnEnemy(float x, float y, float velX, float velY);

/**
 * @brief Actualiza los enemigos con datos recibidos del servidor
 * @param serverEnemies Array de datos de enemigos del servidor
 * @param count Numero de enemigos en el array
 */
void updateEnemiesFromServer(ServerEnemyData* serverEnemies, int count);

/**
 * @brief Obtiene el array de enemigos
 * @return Puntero al array de enemigos
 */
Enemy* getEnemies(void);

/**
 * @brief Obtiene el numero de enemigos activos
 * @return Cantidad de enemigos actualmente activos
 */
int getEnemyCount(void);

#endif // ENEMY_H
