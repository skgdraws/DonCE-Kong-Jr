#include "renderer.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "fruit.h"
#include "assets.h"
#include <string.h>
#include <stdio.h>

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
        // Voltear horizontalmente si el jugador mira hacia la derecha
        SDL_FlipMode flip = player->facingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        SDL_RenderTextureRotated(renderer, playerSpritesheet, &srcRect, &dstRect, 0, NULL, flip);
    } else {
        // Fallback: dibujar rectangulo si no hay sprite
        SDL_FRect playerRect = {player->x, player->y, 32, 16};
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderFillRect(renderer, &playerRect);
    }

    // Dibujar enemigos con sus sprites correspondientes
    SDL_Texture* gatorRedTexture = getGatorRedTexture();
    SDL_Texture* gatorBlueTexture = getGatorBlueTexture();
    
    // Contador de animacion para enemigos (2 frames de 16x16)
    static int enemyAnimCounter = 0;
    static const int ENEMY_FRAME_WIDTH = 16;
    static const int ENEMY_FRAME_HEIGHT = 16;
    static const int ENEMY_FRAME_COUNT = 2;
    static const int ENEMY_ANIM_SPEED = 10; // Cambiar frame cada 10 frames de juego
    
    int currentEnemyFrame = (enemyAnimCounter / ENEMY_ANIM_SPEED) % ENEMY_FRAME_COUNT;
    enemyAnimCounter++;
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            SDL_Texture* enemyTexture = NULL;
            
            // Seleccionar textura segun el tipo de enemigo
            if (enemies[i].type == ENEMY_TYPE_RED) {
                enemyTexture = gatorRedTexture;
            } else if (enemies[i].type == ENEMY_TYPE_BLUE) {
                enemyTexture = gatorBlueTexture;
            }
            
            if (enemyTexture) {
                // Renderizar sprite animado del enemigo (spritesheet 32x16, 2 frames de 16x16)
                SDL_FRect srcRect = {
                    currentEnemyFrame * ENEMY_FRAME_WIDTH,
                    0,
                    ENEMY_FRAME_WIDTH,
                    ENEMY_FRAME_HEIGHT
                };
                SDL_FRect dstRect = {
                    enemies[i].x,
                    enemies[i].y,
                    16.0f,
                    16.0f
                };
                // Voltear verticalmente si es enemigo rojo y se mueve hacia arriba
                SDL_FlipMode flip = SDL_FLIP_NONE;
                if (enemies[i].type == ENEMY_TYPE_RED && enemies[i].movingUp) {
                    flip = SDL_FLIP_VERTICAL;
                }
                SDL_RenderTextureRotated(renderer, enemyTexture, &srcRect, &dstRect, 0, NULL, flip);
            } else {
                // Fallback: dibujar rectangulo coloreado segun tipo
                if (enemies[i].type == ENEMY_TYPE_RED) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
                }
                SDL_FRect enemyRect = {enemies[i].x, enemies[i].y, 16.0f, 16.0f};
                SDL_RenderFillRect(renderer, &enemyRect);
            }
        }
    }

    // Dibujar frutas
    SDL_Texture* fruitTexture = getFruitTexture();
    Fruit* fruits = getFruits();
    
    // Spritesheet de frutas: 3 frames de 16x16 cada uno (48x16 total)
    // Index 0: Orange, Index 1: Banana, Index 2: Strawberry
    static const int FRUIT_FRAME_WIDTH = 16;
    static const int FRUIT_FRAME_HEIGHT = 16;
    
    for (int i = 0; i < MAX_FRUITS; i++) {
        if (fruits[i].active) {
            if (fruitTexture) {
                // Seleccionar frame segun el tipo de fruta
                int frameIndex = (int)fruits[i].type;
                
                SDL_FRect srcRect = {
                    frameIndex * FRUIT_FRAME_WIDTH,
                    0,
                    FRUIT_FRAME_WIDTH,
                    FRUIT_FRAME_HEIGHT
                };
                SDL_FRect dstRect = {
                    fruits[i].x,
                    fruits[i].y,
                    16.0f,
                    16.0f
                };
                SDL_RenderTexture(renderer, fruitTexture, &srcRect, &dstRect);
            } else {
                // Fallback: dibujar rectangulo coloreado segun tipo
                switch (fruits[i].type) {
                    case FRUIT_TYPE_ORANGE:
                        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Naranja
                        break;
                    case FRUIT_TYPE_BANANA:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Amarillo
                        break;
                    case FRUIT_TYPE_STRAWBERRY:
                        SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255); // Rosa/Rojo
                        break;
                    default:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        break;
                }
                SDL_FRect fruitRect = {fruits[i].x, fruits[i].y, 16.0f, 16.0f};
                SDL_RenderFillRect(renderer, &fruitRect);
            }
        }
    }

    // Dibujar HUD (puntuacion y vidas)
    TTF_Font* font = getGameFont();
    SDL_Texture* lifeIconTexture = getLifeIconTexture();
    SDL_Texture* pointsFrameTexture = getPointsTexture();
    
    // Renderizar frame de puntuacion y texto
    if (pointsFrameTexture) {
        // Dibujar el frame de puntos (44x20)
        SDL_FRect pointsFrameRect = {4, 4, 44, 20};
        SDL_RenderTexture(renderer, pointsFrameTexture, NULL, &pointsFrameRect);
    }
    
    if (font) {
        // Renderizar puntuacion (4 digitos, dentro del frame)
        char scoreText[8];
        snprintf(scoreText, sizeof(scoreText), "%04d", player->score % 10000);
        SDL_Color scoreColor = {255, 255, 255, 255};
        size_t scoreLength = strlen(scoreText);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, scoreLength, scoreColor);
        if (scoreSurface) {
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            if (scoreTexture) {
                SDL_SetTextureScaleMode(scoreTexture, SDL_SCALEMODE_NEAREST);
                // Centrar el texto dentro del frame (frame empieza en x=4, ancho=44)
                float textX = 6 + (44 - scoreSurface->w) / 2.0f;
                SDL_FRect scoreRect = {textX, 7, (float)scoreSurface->w, (float)scoreSurface->h};
                SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
                SDL_DestroyTexture(scoreTexture);
            }
            SDL_DestroySurface(scoreSurface);
        }
    }
    
    // Renderizar contador de vidas (esquina superior derecha)
    if (lifeIconTexture) {
        for (int i = 0; i < player->lives; i++) {
            SDL_FRect lifeRect = {224 - 12 - (i * 12), 4, 8, 8};
            SDL_RenderTexture(renderer, lifeIconTexture, NULL, &lifeRect);
        }
    }
}

void renderSpectateMenu(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = getGameFont();
    SDL_Texture* lifeIcon = getLifeIconTexture();
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color selectedColor = {255, 255, 100, 255};

    if (font) {
        // Titulo
        const char* title = "Spectate Game";
        size_t titleLength = strlen(title);
        SDL_Surface* titleSurface = TTF_RenderText_Solid(font, title, titleLength, textColor);
        if (titleSurface) {
            SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture) {
                SDL_SetTextureScaleMode(titleTexture, SDL_SCALEMODE_NEAREST);
                SDL_FRect titleRect = {(224 - titleSurface->w) / 2.0f, 60, (float)titleSurface->w, (float)titleSurface->h};
                SDL_RenderTexture(renderer, titleTexture, NULL, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_DestroySurface(titleSurface);
        }

        // Opciones del menu de espectacion
        const char* spectateOptions[] = {"Game 1", "Game 2", "Back"};
        float maxTextWidth = 0;
        
        for (int i = 0; i < SPECTATE_COUNT; i++) {
            float yPos = 100 + i * 15;
            SDL_Color color = (i == selectedSpectateOption) ? selectedColor : textColor;
            size_t optLength = strlen(spectateOptions[i]);
            SDL_Surface* optSurface = TTF_RenderText_Solid(font, spectateOptions[i], optLength, color);
            if (optSurface) {
                SDL_Texture* optTexture = SDL_CreateTextureFromSurface(renderer, optSurface);
                if (optTexture) {
                    SDL_SetTextureScaleMode(optTexture, SDL_SCALEMODE_NEAREST);
                    float textX = (224 - optSurface->w) / 2.0f;
                    if (optSurface->w > maxTextWidth) {
                        maxTextWidth = optSurface->w;
                    }
                    SDL_FRect optRect = {textX, yPos, (float)optSurface->w, (float)optSurface->h};
                    SDL_RenderTexture(renderer, optTexture, NULL, &optRect);
                    SDL_DestroyTexture(optTexture);
                }
                SDL_DestroySurface(optSurface);
            }
        }

        // Dibujar indicador de seleccion (icono de vida)
        if (lifeIcon) {
            float iconX = (maxTextWidth > 0) ? ((224 - maxTextWidth) / 2.0f - 15) : 75;
            SDL_FRect selectorRect = {iconX, 100 + selectedSpectateOption * 15, 8, 8};
            SDL_RenderTexture(renderer, lifeIcon, NULL, &selectorRect);
        }
    }
}

void renderSpectating(SDL_Renderer* renderer) {
    // Renderizar el juego normal primero
    renderGame(renderer);
    
    // Agregar overlay de "SPECTATING"
    TTF_Font* font = getGameFont();
    if (font) {
        char spectateText[32];
        snprintf(spectateText, sizeof(spectateText), "SPECTATING GAME %d", spectatingGameNumber);
        SDL_Color spectateColor = {255, 255, 0, 255}; // Amarillo
        size_t textLen = strlen(spectateText);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, spectateText, textLen, spectateColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            if (textTexture) {
                SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);
                // Posicionar en la parte inferior central
                SDL_FRect textRect = {
                    (224 - textSurface->w) / 2.0f,
                    256 - 16,
                    (float)textSurface->w,
                    (float)textSurface->h
                };
                SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
            }
            SDL_DestroySurface(textSurface);
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

void renderGameOver(SDL_Renderer* renderer) {
    // Limpiar pantalla con color oscuro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_Font* font = getGameFont();
    SDL_Color titleColor = {255, 50,  50,  255};  // Rojo para "GAME OVER"
    SDL_Color textColor  = {255, 255, 255, 255};  // Blanco para el texto
    SDL_Color scoreColor = {255, 255, 100, 255};  // Amarillo para el puntaje

    if (font) {
        // Titulo "GAME OVER"
        const char* title = "GAME OVER";
        size_t titleLength = strlen(title);
        SDL_Surface* titleSurface = TTF_RenderText_Solid(font, title, titleLength, titleColor);
        if (titleSurface) {
            SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture) {
                SDL_SetTextureScaleMode(titleTexture, SDL_SCALEMODE_NEAREST);
                float titleX = (224 - titleSurface->w) / 2.0f;
                SDL_FRect titleRect = {titleX, 80, (float)titleSurface->w, (float)titleSurface->h};
                SDL_RenderTexture(renderer, titleTexture, NULL, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_DestroySurface(titleSurface);
        }

        // Texto "Final Score:"
        const char* scoreLabel = "Final Score:";
        size_t scoreLabelLength = strlen(scoreLabel);
        SDL_Surface* labelSurface = TTF_RenderText_Solid(font, scoreLabel, scoreLabelLength, textColor);
        if (labelSurface) {
            SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
            if (labelTexture) {
                SDL_SetTextureScaleMode(labelTexture, SDL_SCALEMODE_NEAREST);
                float labelX = (224 - labelSurface->w) / 2.0f;
                SDL_FRect labelRect = {labelX, 110, (float)labelSurface->w, (float)labelSurface->h};
                SDL_RenderTexture(renderer, labelTexture, NULL, &labelRect);
                SDL_DestroyTexture(labelTexture);
            }
            SDL_DestroySurface(labelSurface);
        }

        // Mostrar el puntaje final
        char scoreText[32];
        snprintf(scoreText, sizeof(scoreText), "%d", finalScore);
        size_t scoreLength = strlen(scoreText);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, scoreLength, scoreColor);
        if (scoreSurface) {
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
            if (scoreTexture) {
                SDL_SetTextureScaleMode(scoreTexture, SDL_SCALEMODE_NEAREST);
                float scoreX = (224 - scoreSurface->w) / 2.0f;
                SDL_FRect scoreRect = {scoreX, 130, (float)scoreSurface->w, (float)scoreSurface->h};
                SDL_RenderTexture(renderer, scoreTexture, NULL, &scoreRect);
                SDL_DestroyTexture(scoreTexture);
            }
            SDL_DestroySurface(scoreSurface);
        }

        // Instrucciones
        const char* instructions = "Press SPACE to continue";
        size_t instructionsLength = strlen(instructions);
        SDL_Surface* instrSurface = TTF_RenderText_Solid(font, instructions, instructionsLength, textColor);
        if (instrSurface) {
            SDL_Texture* instrTexture = SDL_CreateTextureFromSurface(renderer, instrSurface);
            if (instrTexture) {
                SDL_SetTextureScaleMode(instrTexture, SDL_SCALEMODE_NEAREST);
                float instrX = (224 - instrSurface->w) / 2.0f;
                SDL_FRect instrRect = {instrX, 180, (float)instrSurface->w, (float)instrSurface->h};
                SDL_RenderTexture(renderer, instrTexture, NULL, &instrRect);
                SDL_DestroyTexture(instrTexture);
            }
            SDL_DestroySurface(instrSurface);
        }
    } else {
        // Fallback sin fuente
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_FRect titleRect = {62, 80, 100, 20};
        SDL_RenderFillRect(renderer, &titleRect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        SDL_FRect scoreRect = {62, 120, 100, 20};
        SDL_RenderFillRect(renderer, &scoreRect);
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
        case GAME_STATE_CONNECTING_SPECTATE:
            renderConnecting(renderer);
            break;
        case GAME_STATE_PLAYING:
            renderGame(renderer);
            break;
        case GAME_STATE_SPECTATING:
            renderSpectating(renderer);
            break;
        case GAME_STATE_GAME_OVER:
            renderGameOver(renderer);
            break;
        case GAME_STATE_QUIT:
            break;
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderer);
}
