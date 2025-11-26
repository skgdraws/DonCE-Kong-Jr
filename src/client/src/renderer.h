#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

/**
 * @brief Funcion principal de renderizado del juego
 * 
 * Determina que renderizar basado en el estado actual del juego.
 * 
 * @param renderer Puntero al renderer de SDL
 */
void render(SDL_Renderer* renderer);

/**
 * @brief Renderiza el menu principal
 * @param renderer Puntero al renderer de SDL
 */
void renderMenu(SDL_Renderer* renderer);

/**
 * @brief Renderiza la pantalla de juego
 * 
 * Dibuja el fondo, jugador, enemigos y otros elementos del juego.
 * 
 * @param renderer Puntero al renderer de SDL
 */
void renderGame(SDL_Renderer* renderer);

#endif // RENDERER_H
