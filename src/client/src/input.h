#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <stdbool.h>

/**
 * @brief Procesa todos los eventos de entrada pendientes
 * @param running Puntero al flag de ejecucion del juego
 */
void handleEvents(bool* running);

/**
 * @brief Maneja la entrada del usuario en el menu
 * @param event Evento de SDL a procesar
 */
void handleMenuInput(SDL_Event* event);

/**
 * @brief Maneja la entrada del usuario durante el juego
 * 
 * Envia comandos al servidor basados en la entrada del usuario.
 * 
 * @param event Evento de SDL a procesar
 */
void handleGameInput(SDL_Event* event);

/**
 * @brief Maneja la entrada del usuario en la pantalla de game over
 * @param event Evento de SDL a procesar
 */
void handleGameOverInput(SDL_Event* event);

#endif // INPUT_H
