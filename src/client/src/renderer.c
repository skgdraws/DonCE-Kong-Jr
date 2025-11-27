#include "renderer.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "assets.h"
#include <string.h>

void renderMenu(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Texture* logoTexture = getLogoTexture();
    TTF_Font* font = getGameFont();

    // Dibujar logo
    if (logoTexture) {
        // Logo: 183x56, centered horizontally at top
        SDL_FRect logoRect = {(224 - 183) / 2.0f, 10, 183, 56};
        SDL_RenderTexture(renderer, logoTexture, NULL, &logoRect);
    } else {
        // Fallback: rectangulo de titulo
        SDL_FRect titleRect = {62, 20, 100, 20};
        SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
        SDL_RenderFillRect(renderer, &titleRect);
    }

    // Array de textos para las opciones
    const char* menuOptions[] = {"Play Game", "Spectate Game", "Credits", "Exit"};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color selectedColor = {255, 255, 100, 255};

    // Calcular la posicion del texto mas largo para determinar donde colocar el icono
    float maxTextWidth = 0;
    float textPositions[MENU_COUNT];
    
    // Dibujar opciones del menu
    for (int i = 0; i < MENU_COUNT; i++) {
        float yPos = 125 + i * 15;
        
        if (font) {
            // Renderizar texto con fuente (SDL3_ttf requiere longitud del string)
            SDL_Color color = (i == selectedOption) ? selectedColor : textColor;
            size_t textLength = strlen(menuOptions[i]);
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuOptions[i], textLength, color);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);
                    // Centrar el texto horizontalmente (ventana de 224px de ancho)
                    float textX = (224 - textSurface->w) / 2.0f;
                    textPositions[i] = textX;
                    if (textSurface->w > maxTextWidth) {
                        maxTextWidth = textSurface->w;
                    }
                    SDL_FRect textRect = {
                        textX,
                        yPos,
                        (float)textSurface->w,
                        (float)textSurface->h
                    };
                    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_DestroySurface(textSurface);
            }
        } else {
            // Fallback: rectangulos de colores centrados
            SDL_FRect optionRect = {75, yPos, 75, 15};
            textPositions[i] = 75;
            
            if (i == selectedOption) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            }
            SDL_RenderFillRect(renderer, &optionRect);
        }
    }

    // Dibujar indicador de seleccion (icono de vida)
    SDL_Texture* lifeIcon = getLifeIconTexture();
    if (lifeIcon) {
        // Posicionar el icono a la izquierda del texto, con margen de 5px
        float iconX = (maxTextWidth > 0) ? ((224 - maxTextWidth) / 2.0f - 15) : 75;
        SDL_FRect selectorRect = {iconX, 125 + selectedOption * 15, 8, 8};
        SDL_RenderTexture(renderer, lifeIcon, NULL, &selectorRect);
    } else {
        // Fallback: rectangulo rojo
        float iconX = (maxTextWidth > 0) ? ((224 - maxTextWidth) / 2.0f - 25) : 75;
        SDL_FRect selectorRect = {iconX, 125 + selectedOption * 15, 8, 8};
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_RenderFillRect(renderer, &selectorRect);
    }
}

void renderGame(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Texture* backgroundTexture = getBackgroundTexture();
    SDL_Texture* playerSpritesheet = getPlayerSpritesheet();
    SDL_Texture* dkTexture = getDKTexture();
    SDL_Texture* cageTexture = getCageTexture();
    SDL_Texture* marioTexture = getMarioTexture();
    Player* player = getPlayer();
    Enemy* enemies = getEnemies();

    // Contador de animacion estatico para DK (3 frames a 48x32 cada uno)
    static int dkAnimCounter = 0;
    static const int DK_FRAME_WIDTH = 48;
    static const int DK_FRAME_HEIGHT = 32;
    static const int DK_FRAME_COUNT = 3;
    static const int DK_ANIM_SPEED = 8; // Cambiar frame cada 8 frames de juego

    // Contador de animacion estatico para Mario (5 frames a 16x16 cada uno)
    static int marioAnimCounter = 0;
    static const int MARIO_FRAME_WIDTH = 16;
    static const int MARIO_FRAME_HEIGHT = 16;
    static const int MARIO_FRAME_COUNT = 2;
    static const int MARIO_ANIM_SPEED = 8; // Cambiar frame cada 8 frames de juego

    // Dibujar el fondo si existe
    if (backgroundTexture) {
        SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);
    } else {
        // Fondo de respaldo si no se carga la imagen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_FRect gameRect = {0, 0, 224, 256};
        SDL_RenderFillRect(renderer, &gameRect);
    }

    // Dibujar Donkey Kong (detras de la jaula)
    if (dkTexture) {
        int currentFrame = (dkAnimCounter / DK_ANIM_SPEED) % DK_FRAME_COUNT;
        SDL_FRect srcRect = {
            currentFrame * DK_FRAME_WIDTH,
            0,
            DK_FRAME_WIDTH,
            DK_FRAME_HEIGHT
        };
        SDL_FRect dstRect = {4, 40, 48, 32};
        SDL_RenderTexture(renderer, dkTexture, &srcRect, &dstRect);
        dkAnimCounter++;
    }

    // Dibujar la jaula (encima de DK)
    if (cageTexture) {
        SDL_FRect cageRect = {4, 40, 48, 32};
        SDL_RenderTexture(renderer, cageTexture, NULL, &cageRect);
    }

    // Dibujar Mario (animado, horizontally flipped)
    if (marioTexture) {
        int currentFrame = (marioAnimCounter / MARIO_ANIM_SPEED) % MARIO_FRAME_COUNT;
        SDL_FRect srcRect = {
            currentFrame * MARIO_FRAME_WIDTH,
            0,
            MARIO_FRAME_WIDTH,
            MARIO_FRAME_HEIGHT
        };
        SDL_FRect dstRect = {56, 56, 16, 16};
        SDL_RenderTextureRotated(renderer, marioTexture, &srcRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        marioAnimCounter++;
    }

    // Dibujar el bloque del jugador
    if (playerSpritesheet) {
        // Usar el indice de sprite directamente
        // Spritesheet: 448x16 (14 frames de 32x16 cada uno)
        SDL_FRect srcRect = {
            player->spriteIndex * PLAYER_SPRITE_WIDTH,
            0,
            PLAYER_SPRITE_WIDTH,
            PLAYER_SPRITE_HEIGHT
        };
        SDL_FRect dstRect = {
            player->x,
            player->y,
            32,  // 32x16 at native resolution
            16
        };
        SDL_RenderTexture(renderer, playerSpritesheet, &srcRect, &dstRect);
    } else {
        // Fallback: dibujar rectangulo si no hay sprite
        SDL_FRect playerRect = {player->x, player->y, 32, 16};
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderFillRect(renderer, &playerRect);
    }

    // Dibujar enemigos
    SDL_SetRenderDrawColor(renderer, 255, 50, 200, 255);
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            SDL_FRect enemyRect = {enemies[i].x, enemies[i].y, enemies[i].size, enemies[i].size};
            SDL_RenderFillRect(renderer, &enemyRect);
        }
    }
}

void renderSpectateMenu(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = getGameFont();
    SDL_Color textColor = {255, 255, 255, 255};

    if (font) {
        // Titulo
        const char* title = "Spectate Game";
        size_t titleLength = strlen(title);
        SDL_Surface* titleSurface = TTF_RenderText_Solid(font, title, titleLength, textColor);
        if (titleSurface) {
            SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture) {
                SDL_SetTextureScaleMode(titleTexture, SDL_SCALEMODE_NEAREST);
                SDL_FRect titleRect = {(224 - titleSurface->w) / 2.0f, 80, (float)titleSurface->w, (float)titleSurface->h};
                SDL_RenderTexture(renderer, titleTexture, NULL, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_DestroySurface(titleSurface);
        }

        // Mensaje
        const char* message = "Press Enter to return";
        size_t messageLength = strlen(message);
        SDL_Surface* msgSurface = TTF_RenderText_Solid(font, message, messageLength, textColor);
        if (msgSurface) {
            SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
            if (msgTexture) {
                SDL_SetTextureScaleMode(msgTexture, SDL_SCALEMODE_NEAREST);
                SDL_FRect msgRect = {(224 - msgSurface->w) / 2.0f, 120, (float)msgSurface->w, (float)msgSurface->h};
                SDL_RenderTexture(renderer, msgTexture, NULL, &msgRect);
                SDL_DestroyTexture(msgTexture);
            }
            SDL_DestroySurface(msgSurface);
        }
    }
}

void renderCredits(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = getGameFont();
    SDL_Color textColor = {255, 255, 255, 255};

    if (font) {
        const char* credits[] = {
            "Credits",
            "",
            "Proyecto IV",
            "Paradigmas de Programacion",
            "",
            "Pamela Chacon - 2023110706",
            "Kevin Ruiz - 2018170538",
            "Franco Sagot - 2022211182",
            "",
            "Press ESC to return"
        };
        
        for (int i = 0; i < 10; i++) {
            if (strlen(credits[i]) > 0) {
                size_t textLength = strlen(credits[i]);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, credits[i], textLength, textColor);
                if (textSurface) {
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    if (textTexture) {
                        SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);
                        SDL_FRect textRect = {(224 - textSurface->w) / 2.0f, 20 + i * 20, (float)textSurface->w, (float)textSurface->h};
                        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
                        SDL_DestroyTexture(textTexture);
                    }
                    SDL_DestroySurface(textSurface);
                }
            }
        }
    }
}

void renderConnecting(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = getGameFont();
    SDL_Color textColor = {255, 255, 100, 255};

    if (font) {
        const char* message = "Connecting to server...";
        size_t messageLength = strlen(message);
        SDL_Surface* msgSurface = TTF_RenderText_Solid(font, message, messageLength, textColor);
        if (msgSurface) {
            SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
            if (msgTexture) {
                SDL_SetTextureScaleMode(msgTexture, SDL_SCALEMODE_NEAREST);
                SDL_FRect msgRect = {(224 - msgSurface->w) / 2.0f, 120, (float)msgSurface->w, (float)msgSurface->h};
                SDL_RenderTexture(renderer, msgTexture, NULL, &msgRect);
                SDL_DestroyTexture(msgTexture);
            }
            SDL_DestroySurface(msgSurface);
        }
    }
}

void renderSpectating(SDL_Renderer* renderer) {
    // Renderizar igual que el juego pero con indicador de espectador
    renderGame(renderer);
    
    TTF_Font* font = getGameFont();
    SDL_Color textColor = {255, 255, 100, 255};

    if (font) {
        const char* message = "SPECTATING";
        size_t messageLength = strlen(message);
        SDL_Surface* msgSurface = TTF_RenderText_Solid(font, message, messageLength, textColor);
        if (msgSurface) {
            SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
            if (msgTexture) {
                SDL_SetTextureScaleMode(msgTexture, SDL_SCALEMODE_NEAREST);
                SDL_FRect msgRect = {10, 10, (float)msgSurface->w, (float)msgSurface->h};
                SDL_RenderTexture(renderer, msgTexture, NULL, &msgRect);
                SDL_DestroyTexture(msgTexture);
            }
            SDL_DestroySurface(msgSurface);
        }
    }
}

void render(SDL_Renderer* renderer) {
    switch (gameState) {
        case GAME_STATE_MENU:
            renderMenu(renderer);
            break;
        case GAME_STATE_SPECTATE:
            renderSpectateMenu(renderer);
            break;
        case GAME_STATE_CREDITS:
            renderCredits(renderer);
            break;
        case GAME_STATE_CONNECTING:
            renderConnecting(renderer);
            break;
        case GAME_STATE_PLAYING:
            renderGame(renderer);
            break;
        case GAME_STATE_SPECTATING:
            renderSpectating(renderer);
            break;
        case GAME_STATE_QUIT:
            break;
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderer);
}
