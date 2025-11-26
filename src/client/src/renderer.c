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
        SDL_FRect logoRect = {106, 40, 300, 120};
        SDL_RenderTexture(renderer, logoTexture, NULL, &logoRect);
    } else {
        // Fallback: rectangulo de titulo
        SDL_FRect titleRect = {156, 80, 200, 40};
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
        float yPos = 275 + i * 35;
        
        if (font) {
            // Renderizar texto con fuente (SDL3_ttf requiere longitud del string)
            SDL_Color color = (i == selectedOption) ? selectedColor : textColor;
            size_t textLength = strlen(menuOptions[i]);
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuOptions[i], textLength, color);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (textTexture) {
                    // Centrar el texto horizontalmente (ventana de 512px de ancho)
                    float textX = (512 - textSurface->w) / 2.0f;
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
            SDL_FRect optionRect = {181, yPos, 150, 35};
            textPositions[i] = 181;
            
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
        // Posicionar el icono a la izquierda del texto, con margen de 10px
        float iconX = (maxTextWidth > 0) ? ((512 - maxTextWidth) / 2.0f - 30) : 150;
        SDL_FRect selectorRect = {iconX, 270 + selectedOption * 35, 20, 20};
        SDL_RenderTexture(renderer, lifeIcon, NULL, &selectorRect);
    } else {
        // Fallback: rectangulo rojo
        float iconX = (maxTextWidth > 0) ? ((512 - maxTextWidth) / 2.0f - 30) : 150;
        SDL_FRect selectorRect = {iconX, 270 + selectedOption * 35, 20, 25};
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
    Player* player = getPlayer();
    Enemy* enemies = getEnemies();

    // Dibujar el fondo si existe
    if (backgroundTexture) {
        SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);
    } else {
        // Fondo de respaldo si no se carga la imagen
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
        SDL_FRect gameRect = {50, 50, 412, 348};
        SDL_RenderFillRect(renderer, &gameRect);
    }

    // Dibujar el bloque del jugador
    if (playerSpritesheet) {
        // Usar el indice de sprite directamente
        SDL_FRect srcRect = {
            player->spriteIndex * PLAYER_SPRITE_WIDTH,
            0,
            PLAYER_SPRITE_WIDTH,
            PLAYER_SPRITE_HEIGHT
        };
        SDL_FRect dstRect = {
            player->x,
            player->y,
            PLAYER_SPRITE_WIDTH * 2,  // Escalar 2x
            PLAYER_SPRITE_HEIGHT * 2
        };
        SDL_RenderTexture(renderer, playerSpritesheet, &srcRect, &dstRect);
    } else {
        // Fallback: dibujar rectangulo si no hay sprite
        SDL_FRect playerRect = {player->x, player->y, player->size, player->size};
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
                SDL_FRect titleRect = {(512 - titleSurface->w) / 2.0f, 150, (float)titleSurface->w, (float)titleSurface->h};
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
                SDL_FRect msgRect = {(512 - msgSurface->w) / 2.0f, 250, (float)msgSurface->w, (float)msgSurface->h};
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
                        SDL_FRect textRect = {(512 - textSurface->w) / 2.0f, 50 + i * 40, (float)textSurface->w, (float)textSurface->h};
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
                SDL_FRect msgRect = {(512 - msgSurface->w) / 2.0f, 220, (float)msgSurface->w, (float)msgSurface->h};
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
