#include "input.h"
#include "game_state.h"
#include "enemy.h"
#include <SDL3/SDL.h>
#include <stdlib.h>

void handleMenuInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_UP:
                selectedOption = (selectedOption - 1 + MENU_COUNT) % MENU_COUNT;
                break;
            case SDLK_DOWN:
                selectedOption = (selectedOption + 1) % MENU_COUNT;
                break;
            case SDLK_RETURN:
            case SDLK_SPACE:
                switch (selectedOption) {
                    case MENU_START:
                        gameState = GAME_STATE_PLAYING;
                        SDL_Log("Iniciando juego...");
                        break;
                    case MENU_OPTIONS:
                        SDL_Log("Opciones - Proximamente");
                        break;
                    case MENU_EXIT:
                        gameState = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SDLK_ESCAPE:
                gameState = GAME_STATE_QUIT;
                break;
        }
    }
}

void handleGameInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
                gameState = GAME_STATE_MENU;
                break;
            case SDLK_W:
            case SDLK_UP:
                // TODO: Enviar comando "move_up" al servidor
                SDL_Log("Input: Move Up (enviar al servidor)");
                break;
            case SDLK_S:
            case SDLK_DOWN:
                // TODO: Enviar comando "move_down" al servidor
                SDL_Log("Input: Move Down (enviar al servidor)");
                break;
            case SDLK_A:
            case SDLK_LEFT:
                // TODO: Enviar comando "move_left" al servidor
                SDL_Log("Input: Move Left (enviar al servidor)");
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                // TODO: Enviar comando "move_right" al servidor
                SDL_Log("Input: Move Right (enviar al servidor)");
                break;
            case SDLK_E:
                // Debug: Spawn enemy
                {
                    float spawnX = (float)(rand() % 400 + 50);
                    float spawnY = 50.0f;
                    float dirX = (rand() % 2 == 0) ? 1.0f : -1.0f;
                    float dirY = 1.0f;
                    spawnEnemy(spawnX, spawnY, dirX * ENEMY_SPEED, dirY * ENEMY_SPEED);
                }
                break;
        }
    } else if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.key) {
            case SDLK_W:
            case SDLK_UP:
            case SDLK_S:
            case SDLK_DOWN:
            case SDLK_A:
            case SDLK_LEFT:
            case SDLK_D:
            case SDLK_RIGHT:
                // TODO: Enviar comando "stop" al servidor
                SDL_Log("Input: Stop (enviar al servidor)");
                break;
        }
    }
}

void handleEvents(bool* running) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            *running = false;
            return;
        }

        if (gameState == GAME_STATE_MENU) {
            handleMenuInput(&event);
        } else if (gameState == GAME_STATE_PLAYING) {
            handleGameInput(&event);
        }
    }

    // Verificar si se debe salir
    if (gameState == GAME_STATE_QUIT) {
        *running = false;
    }
}
