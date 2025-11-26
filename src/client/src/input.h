#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <stdbool.h>

// Funcion para procesar eventos
void handleEvents(bool* running);

// Funcion para manejar input del menu
void handleMenuInput(SDL_Event* event);

// Funcion para manejar input del juego
void handleGameInput(SDL_Event* event);

#endif // INPUT_H
