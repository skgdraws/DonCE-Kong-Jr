#include "assets.h"

// Texturas
static SDL_Texture *backgroundTexture = NULL;
static SDL_Texture *playerSpritesheet = NULL;

SDL_Texture* getBackgroundTexture(void) {
    return backgroundTexture;
}

SDL_Texture* getPlayerSpritesheet(void) {
    return playerSpritesheet;
}

void loadAssets(SDL_Renderer* renderer) {
    // Establecer filtro de escalado a nearest neighbor para pixeles nitidos
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "0");

    // Cargar imagen de fondo
    SDL_Surface *bgSurface = SDL_LoadBMP("assets/img/bg.bmp");
    if (bgSurface) {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_DestroySurface(bgSurface);
        if (backgroundTexture) {
            // Configurar filtro nearest neighbor para la textura
            SDL_SetTextureScaleMode(backgroundTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Fondo cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del fondo: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar fondo: %s", SDL_GetError());
    }

    // Cargar spritesheet del jugador
    SDL_Surface *playerSurface = SDL_LoadBMP("assets/img/dk-jr.bmp");
    if (playerSurface) {
        playerSpritesheet = SDL_CreateTextureFromSurface(renderer, playerSurface);
        SDL_DestroySurface(playerSurface);
        if (playerSpritesheet) {
            SDL_SetTextureScaleMode(playerSpritesheet, SDL_SCALEMODE_NEAREST);
            SDL_Log("Spritesheet del jugador cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del spritesheet: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar spritesheet: %s", SDL_GetError());
    }
}

void cleanupAssets(void) {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;
    }
    if (playerSpritesheet) {
        SDL_DestroyTexture(playerSpritesheet);
        playerSpritesheet = NULL;
    }
}
