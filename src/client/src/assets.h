#ifndef ASSETS_H
#define ASSETS_H

#include <SDL3/SDL.h>

// Funcion para cargar assets
void loadAssets(SDL_Renderer* renderer);

// Funcion para liberar assets
void cleanupAssets(void);

// Obtener texturas
SDL_Texture* getBackgroundTexture(void);
SDL_Texture* getPlayerSpritesheet(void);

#endif // ASSETS_H
