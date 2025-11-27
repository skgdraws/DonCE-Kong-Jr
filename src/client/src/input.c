#include "input.h"
#include "game_state.h"
#include "enemy.h"
#include "network.h"
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
                        gameState = GAME_STATE_CONNECTING;
                        SDL_Log("Conectando al servidor...");
                        break;
                    case MENU_SPECTATE:
                        gameState = GAME_STATE_SPECTATE;
                        SDL_Log("Menu de espectacion");
                        break;
                    case MENU_CREDITS:
                        gameState = GAME_STATE_CREDITS;
                        SDL_Log("Mostrando creditos");
                        break;
                    case MENU_EXIT:
                        gameState = GAME_STATE_QUIT;
                        break;
                }
                break;
            case SDLK_ESCAPE:
                // Disconnect from server when returning to menu
                if (isConnected()) {
                    SDL_Log("Desconectando del servidor...");
                    disconnectFromServer();
                }
                gameState = GAME_STATE_MENU;
                break;
        }
    }
}

void handleGameInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
                // Disconnect from server when returning to menu
                if (isConnected()) {
                    SDL_Log("Desconectando del servidor...");
                    disconnectFromServer();
                }
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
                // Debug: Solicitar spawn de enemigo al servidor
                // TODO: Enviar comando "spawn_enemy" al servidor
                SDL_Log("Input: Spawn Enemy (enviar al servidor)");
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

void handleSpectateMenuInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
            case SDLK_RETURN:
                gameState = GAME_STATE_MENU;
                break;
        }
    }
}

void handleCreditsInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
            case SDLK_RETURN:
            case SDLK_SPACE:
                gameState = GAME_STATE_MENU;
                break;
        }
    }
}

void handleConnectingInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_ESCAPE) {
            gameState = GAME_STATE_MENU;
        }
    }
}

void handleSpectatingInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_ESCAPE) {
            // Disconnect from server when returning to menu
            if (isConnected()) {
                SDL_Log("Desconectando del servidor...");
                disconnectFromServer();
            }
            gameState = GAME_STATE_MENU;
        }
    }
}

void handleEvents(bool* running) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            // Disconnect from server when quitting
            if (isConnected()) {
                SDL_Log("Desconectando del servidor antes de cerrar...");
                disconnectFromServer();
            }
            *running = false;
            return;
        }

        switch (gameState) {
            case GAME_STATE_MENU:
                handleMenuInput(&event);
                break;
            case GAME_STATE_SPECTATE:
                handleSpectateMenuInput(&event);
                break;
            case GAME_STATE_CREDITS:
                handleCreditsInput(&event);
                break;
            case GAME_STATE_CONNECTING:
                handleConnectingInput(&event);
                break;
            case GAME_STATE_PLAYING:
                handleGameInput(&event);
                break;
            case GAME_STATE_SPECTATING:
                handleSpectatingInput(&event);
                break;
            case GAME_STATE_QUIT:
                break;
        }
    }

    // Verificar si se debe salir
    if (gameState == GAME_STATE_QUIT) {
        *running = false;
    }
}
