#include "renderer.h"
#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "assets.h"

void renderMenu(SDL_Renderer* renderer) {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
    SDL_RenderClear(renderer);

    // Dibujar titulo
    SDL_FRect titleRect = {156, 80, 200, 40};
    SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
    SDL_RenderFillRect(renderer, &titleRect);

    // Dibujar opciones del menu
    for (int i = 0; i < MENU_COUNT; i++) {
        SDL_FRect optionRect = {180, 180 + i * 50, 150, 35};
        
        if (i == selectedOption) {
            // Opcion seleccionada - color brillante
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
        } else {
            // Opcion no seleccionada - color apagado
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }
        SDL_RenderFillRect(renderer, &optionRect);
    }

    // Dibujar indicador de seleccion
    SDL_FRect selectorRect = {150, 185 + selectedOption * 50, 20, 25};
    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_RenderFillRect(renderer, &selectorRect);
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

void render(SDL_Renderer* renderer) {
    if (gameState == GAME_STATE_MENU) {
        renderMenu(renderer);
    } else if (gameState == GAME_STATE_PLAYING) {
        renderGame(renderer);
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderer);
}
