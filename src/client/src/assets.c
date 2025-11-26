#include "assets.h"

// Texturas
static SDL_Texture *backgroundTexture = NULL;
static SDL_Texture *playerSpritesheet = NULL;
static SDL_Texture *logoTexture = NULL;
static SDL_Texture *lifeIconTexture = NULL;

// Fuentes
static TTF_Font *gameFont = NULL;

SDL_Texture* getBackgroundTexture(void) {
    return backgroundTexture;
}

SDL_Texture* getPlayerSpritesheet(void) {
    return playerSpritesheet;
}

SDL_Texture* getLogoTexture(void) {
    return logoTexture;
}

SDL_Texture* getLifeIconTexture(void) {
    return lifeIconTexture;
}

TTF_Font* getGameFont(void) {
    return gameFont;
}

void loadAssets(SDL_Renderer* renderer) {
    // Establecer filtro de escalado a nearest neighbor para pixeles nitidos
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "0");

    // Inicializar SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("Error al inicializar SDL_ttf: %s", SDL_GetError());
    } else {
        // Cargar fuente
        gameFont = TTF_OpenFont("assets/font/kongtext.ttf", 16);
        if (gameFont) {
            SDL_Log("Fuente cargada correctamente");
        } else {
            SDL_Log("Error al cargar fuente: %s", SDL_GetError());
        }
    }

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

    // Cargar logo
    SDL_Surface *logoSurface = SDL_LoadBMP("assets/img/logo.bmp");
    if (logoSurface) {
        logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
        SDL_DestroySurface(logoSurface);
        if (logoTexture) {
            SDL_SetTextureScaleMode(logoTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Logo cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del logo: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar logo: %s", SDL_GetError());
    }

    // Cargar icono de vida
    SDL_Surface *lifeIconSurface = SDL_LoadBMP("assets/img/life-icon.bmp");
    if (lifeIconSurface) {
        lifeIconTexture = SDL_CreateTextureFromSurface(renderer, lifeIconSurface);
        SDL_DestroySurface(lifeIconSurface);
        if (lifeIconTexture) {
            SDL_SetTextureScaleMode(lifeIconTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Icono de vida cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del icono de vida: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar icono de vida: %s", SDL_GetError());
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
    if (logoTexture) {
        SDL_DestroyTexture(logoTexture);
        logoTexture = NULL;
    }
    if (lifeIconTexture) {
        SDL_DestroyTexture(lifeIconTexture);
        lifeIconTexture = NULL;
    }
    if (gameFont) {
        TTF_CloseFont(gameFont);
        gameFont = NULL;
    }
    TTF_Quit();
}
