#include "fruit.h"
#include <SDL3/SDL.h>

// Array de frutas
static Fruit fruits[MAX_FRUITS] = {0};
static int fruitCount = 0;

Fruit* getFruits(void) {
    return fruits;
}

int getFruitCount(void) {
    return fruitCount;
}

void updateFruitsFromServer(ServerFruitData* serverFruits, int count) {
    // Desactivar todas las frutas primero
    for (int i = 0; i < MAX_FRUITS; i++) {
        fruits[i].active = false;
    }
    
    fruitCount = 0;
    
    // Actualizar con datos del servidor
    for (int i = 0; i < count && i < MAX_FRUITS; i++) {
        if (serverFruits[i].active) {
            fruits[i].x = serverFruits[i].x;
            fruits[i].y = serverFruits[i].y;
            fruits[i].size = FRUIT_SIZE;
            fruits[i].type = serverFruits[i].type;
            fruits[i].active = true;
            fruitCount++;
        }
    }
}
