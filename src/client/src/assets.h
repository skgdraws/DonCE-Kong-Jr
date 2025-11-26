#ifndef ASSETS_H
#define ASSETS_H

#include <SDL3/SDL.h>

/**
 * @brief Carga todos los assets del juego (texturas, sprites)
 * @param renderer Puntero al renderer de SDL para crear las texturas
 */
void loadAssets(SDL_Renderer* renderer);

/**
 * @brief Libera todos los assets cargados de la memoria
 */
void cleanupAssets(void);

/**
 * @brief Obtiene la textura del fondo
 * @return Puntero a la textura del fondo, o NULL si no esta cargada
 */
SDL_Texture* getBackgroundTexture(void);

/**
 * @brief Obtiene el spritesheet del jugador
 * @return Puntero al spritesheet del jugador, o NULL si no esta cargado
 */
SDL_Texture* getPlayerSpritesheet(void);

#endif // ASSETS_H
