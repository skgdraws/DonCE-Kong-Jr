#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

// Funcion principal de renderizado
void render(SDL_Renderer* renderer);

// Funcion para renderizar el menu
void renderMenu(SDL_Renderer* renderer);

// Funcion para renderizar el juego
void renderGame(SDL_Renderer* renderer);

#endif // RENDERER_H
