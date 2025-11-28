#ifndef ASSETS_H
#define ASSETS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

/**
 * @brief Carga todos los assets del juego (texturas, sprites, fuentes)
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

/**
 * @brief Obtiene la textura del logo
 * @return Puntero a la textura del logo, o NULL si no esta cargada
 */
SDL_Texture* getLogoTexture(void);

/**
 * @brief Obtiene la textura del icono de vida
 * @return Puntero a la textura del icono de vida, o NULL si no esta cargada
 */
SDL_Texture* getLifeIconTexture(void);

/**
 * @brief Obtiene la fuente del juego
 * @return Puntero a la fuente TTF, o NULL si no esta cargada
 */
TTF_Font* getGameFont(void);

/**
 * @brief Obtiene la textura de puntos
 * @return Puntero a la textura de puntos, o NULL si no esta cargada
 */
SDL_Texture* getPointsTexture(void);

/**
 * @brief Obtiene la textura del contador de puntos
 * @return Puntero a la textura del contador de puntos, o NULL si no esta cargada
 */
SDL_Texture* getPointTallyTexture(void);

/**
 * @brief Obtiene la textura de Mario
 * @return Puntero a la textura de Mario, o NULL si no esta cargada
 */
SDL_Texture* getMarioTexture(void);

/**
 * @brief Obtiene la textura del cocodrilo rojo
 * @return Puntero a la textura del cocodrilo rojo, o NULL si no esta cargada
 */
SDL_Texture* getGatorRedTexture(void);

/**
 * @brief Obtiene la textura del cocodrilo azul
 * @return Puntero a la textura del cocodrilo azul, o NULL si no esta cargada
 */
SDL_Texture* getGatorBlueTexture(void);

/**
 * @brief Obtiene la textura de fruta
 * @return Puntero a la textura de fruta, o NULL si no esta cargada
 */
SDL_Texture* getFruitTexture(void);

/**
 * @brief Obtiene la textura de Donkey Kong
 * @return Puntero a la textura de DK, o NULL si no esta cargada
 */
SDL_Texture* getDKTexture(void);

/**
 * @brief Obtiene la textura de la jaula
 * @return Puntero a la textura de la jaula, o NULL si no esta cargada
 */
SDL_Texture* getCageTexture(void);

#endif // ASSETS_H
