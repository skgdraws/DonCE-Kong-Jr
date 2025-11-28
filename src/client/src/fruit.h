#ifndef FRUIT_H
#define FRUIT_H

#include <stdbool.h>

// Constantes de las frutas
#define MAX_FRUITS 20
#define FRUIT_SIZE 16.0f  // Tamaño del sprite de fruta (16x16)

/**
 * @brief Tipos de frutas en el juego (indices del spritesheet)
 */
typedef enum {
    FRUIT_TYPE_ORANGE = 0,     ///< Naranja (indice 0)
    FRUIT_TYPE_BANANA = 1,     ///< Banana (indice 1)
    FRUIT_TYPE_STRAWBERRY = 2  ///< Fresa (indice 2)
} FruitType;

/**
 * @brief Estructura que representa una fruta en el juego
 */
typedef struct {
    float x;           ///< Posicion X de la fruta
    float y;           ///< Posicion Y de la fruta
    float size;        ///< Tamaño de la fruta para colisiones
    FruitType type;    ///< Tipo de fruta
    bool active;       ///< Estado de activacion de la fruta
} Fruit;

/**
 * @brief Estructura de datos de fruta recibida del servidor
 */
typedef struct {
    float x;           ///< Posicion X de la fruta
    float y;           ///< Posicion Y de la fruta
    FruitType type;    ///< Tipo de fruta
    bool active;       ///< Estado de activacion de la fruta
} ServerFruitData;

/**
 * @brief Actualiza las frutas con datos recibidos del servidor
 * @param serverFruits Array de datos de frutas del servidor
 * @param count Numero de frutas en el array
 */
void updateFruitsFromServer(ServerFruitData* serverFruits, int count);

/**
 * @brief Obtiene el array de frutas
 * @return Puntero al array de frutas
 */
Fruit* getFruits(void);

/**
 * @brief Obtiene el numero de frutas activas
 * @return Cantidad de frutas actualmente activas
 */
int getFruitCount(void);

#endif // FRUIT_H
