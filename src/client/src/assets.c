#include "assets.h"

// Texturas
static SDL_Texture *backgroundTexture = NULL;
static SDL_Texture *playerSpritesheet = NULL;
static SDL_Texture *logoTexture = NULL;
static SDL_Texture *lifeIconTexture = NULL;
static SDL_Texture *pointsTexture = NULL;
static SDL_Texture *pointTallyTexture = NULL;
static SDL_Texture *marioTexture = NULL;
static SDL_Texture *gatorRedTexture = NULL;
static SDL_Texture *gatorBlueTexture = NULL;
static SDL_Texture *fruitTexture = NULL;
static SDL_Texture *dkTexture = NULL;
static SDL_Texture *cageTexture = NULL;

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

SDL_Texture* getPointsTexture(void) {
    return pointsTexture;
}

SDL_Texture* getPointTallyTexture(void) {
    return pointTallyTexture;
}

SDL_Texture* getMarioTexture(void) {
    return marioTexture;
}

SDL_Texture* getGatorRedTexture(void) {
    return gatorRedTexture;
}

SDL_Texture* getGatorBlueTexture(void) {
    return gatorBlueTexture;
}

SDL_Texture* getFruitTexture(void) {
    return fruitTexture;
}

SDL_Texture* getDKTexture(void) {
    return dkTexture;
}

SDL_Texture* getCageTexture(void) {
    return cageTexture;
}

void loadAssets(SDL_Renderer* renderer) {
    // Establecer filtro de escalado a nearest neighbor para pixeles nitidos
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "0");

    // Inicializar SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("Error al inicializar SDL_ttf: %s", SDL_GetError());
    } else {
        // Cargar fuente
        gameFont = TTF_OpenFont("assets/font/kongtext.ttf", 8);
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

    // Cargar textura de puntos
    SDL_Surface *pointsSurface = SDL_LoadBMP("assets/img/points.bmp");
    if (pointsSurface) {
        pointsTexture = SDL_CreateTextureFromSurface(renderer, pointsSurface);
        SDL_DestroySurface(pointsSurface);
        if (pointsTexture) {
            SDL_SetTextureScaleMode(pointsTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Textura de puntos cargada correctamente");
        } else {
            SDL_Log("Error al crear textura de puntos: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar textura de puntos: %s", SDL_GetError());
    }

    // Cargar sprite de Mario
    SDL_Surface *marioSurface = SDL_LoadBMP("assets/img/mario.bmp");
    if (marioSurface) {
        marioTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
        SDL_DestroySurface(marioSurface);
        if (marioTexture) {
            SDL_SetTextureScaleMode(marioTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de Mario cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de Mario: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de Mario: %s", SDL_GetError());
    }

    // Cargar sprite de cocodrilo rojo
    SDL_Surface *gatorRedSurface = SDL_LoadBMP("assets/img/gator-red.bmp");
    if (gatorRedSurface) {
        gatorRedTexture = SDL_CreateTextureFromSurface(renderer, gatorRedSurface);
        SDL_DestroySurface(gatorRedSurface);
        if (gatorRedTexture) {
            SDL_SetTextureScaleMode(gatorRedTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de cocodrilo rojo cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de cocodrilo rojo: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de cocodrilo rojo: %s", SDL_GetError());
    }

    // Cargar sprite de cocodrilo azul
    SDL_Surface *gatorBlueSurface = SDL_LoadBMP("assets/img/gator-blue.bmp");
    if (gatorBlueSurface) {
        gatorBlueTexture = SDL_CreateTextureFromSurface(renderer, gatorBlueSurface);
        SDL_DestroySurface(gatorBlueSurface);
        if (gatorBlueTexture) {
            SDL_SetTextureScaleMode(gatorBlueTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de cocodrilo azul cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de cocodrilo azul: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de cocodrilo azul: %s", SDL_GetError());
    }

    // Cargar sprite de fruta
    SDL_Surface *fruitSurface = SDL_LoadBMP("assets/img/fruit.bmp");
    if (fruitSurface) {
        fruitTexture = SDL_CreateTextureFromSurface(renderer, fruitSurface);
        SDL_DestroySurface(fruitSurface);
        if (fruitTexture) {
            SDL_SetTextureScaleMode(fruitTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de fruta cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de fruta: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de fruta: %s", SDL_GetError());
    }

    // Cargar sprite de DK
    SDL_Surface *dkSurface = SDL_LoadBMP("assets/img/dk.bmp");
    if (dkSurface) {
        dkTexture = SDL_CreateTextureFromSurface(renderer, dkSurface);
        SDL_DestroySurface(dkSurface);
        if (dkTexture) {
            SDL_SetTextureScaleMode(dkTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de DK cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de DK: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de DK: %s", SDL_GetError());
    }

    // Cargar sprite de jaula
    SDL_Surface *cageSurface = SDL_LoadBMP("assets/img/cage.bmp");
    if (cageSurface) {
        cageTexture = SDL_CreateTextureFromSurface(renderer, cageSurface);
        SDL_DestroySurface(cageSurface);
        if (cageTexture) {
            SDL_SetTextureScaleMode(cageTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Sprite de jaula cargado correctamente");
        } else {
            SDL_Log("Error al crear textura de jaula: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar sprite de jaula: %s", SDL_GetError());
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
    if (pointsTexture) {
        SDL_DestroyTexture(pointsTexture);
        pointsTexture = NULL;
    }
    if (pointTallyTexture) {
        SDL_DestroyTexture(pointTallyTexture);
        pointTallyTexture = NULL;
    }
    if (marioTexture) {
        SDL_DestroyTexture(marioTexture);
        marioTexture = NULL;
    }
    if (gatorRedTexture) {
        SDL_DestroyTexture(gatorRedTexture);
        gatorRedTexture = NULL;
    }
    if (gatorBlueTexture) {
        SDL_DestroyTexture(gatorBlueTexture);
        gatorBlueTexture = NULL;
    }
    if (fruitTexture) {
        SDL_DestroyTexture(fruitTexture);
        fruitTexture = NULL;
    }
    if (dkTexture) {
        SDL_DestroyTexture(dkTexture);
        dkTexture = NULL;
    }
    if (cageTexture) {
        SDL_DestroyTexture(cageTexture);
        cageTexture = NULL;
    }
    if (gameFont) {
        TTF_CloseFont(gameFont);
        gameFont = NULL;
    }
    TTF_Quit();
}
