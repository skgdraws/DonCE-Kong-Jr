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
                if (isConnected()) {
                    sendCommandToServer("climb_up");
                    SDL_Log("Sent: climb_up");
                }
                break;
            case SDLK_S:
            case SDLK_DOWN:
                if (isConnected()) {
                    sendCommandToServer("climb_down");
                    SDL_Log("Sent: climb_down");
                }
                break;
            case SDLK_A:
            case SDLK_LEFT:
                if (isConnected()) {
                    sendCommandToServer("move_left");
                    SDL_Log("Sent: move_left");
                }
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                if (isConnected()) {
                    sendCommandToServer("move_right");
                    SDL_Log("Sent: move_right");
                }
                break;
            case SDLK_SPACE:
                if (isConnected()) {
                    sendCommandToServer("jump");
                    SDL_Log("Sent: jump");
                }
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
                if (isConnected()) {
                    sendCommandToServer("stop");
                    SDL_Log("Sent: stop");
                }
                break;
        }
    }
}

void handleSpectateMenuInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_UP:
                selectedSpectateOption = (selectedSpectateOption - 1 + SPECTATE_COUNT) % SPECTATE_COUNT;
                break;
            case SDLK_DOWN:
                selectedSpectateOption = (selectedSpectateOption + 1) % SPECTATE_COUNT;
                break;
            case SDLK_RETURN:
            case SDLK_SPACE:
                switch (selectedSpectateOption) {
                    case SPECTATE_GAME_1:
                        spectatingGameNumber = 1;
                        gameState = GAME_STATE_CONNECTING_SPECTATE;
                        SDL_Log("Conectando para espectar Juego 1...");
                        break;
                    case SPECTATE_GAME_2:
                        spectatingGameNumber = 2;
                        gameState = GAME_STATE_CONNECTING_SPECTATE;
                        SDL_Log("Conectando para espectar Juego 2...");
                        break;
                    case SPECTATE_BACK:
                        gameState = GAME_STATE_MENU;
                        break;
                    default:
                        break;
                }
                break;
            case SDLK_ESCAPE:
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

void handleGameOverInput(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_SPACE:
            case SDLK_RETURN:
            case SDLK_ESCAPE:
                // Volver al menú principal
                gameState = GAME_STATE_MENU;
                break;
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
            case GAME_STATE_CONNECTING_SPECTATE:
                handleConnectingInput(&event);
                break;
            case GAME_STATE_PLAYING:
                handleGameInput(&event);
                break;
            case GAME_STATE_SPECTATING:
                handleSpectatingInput(&event);
                break;
            case GAME_STATE_GAME_OVER:
                handleGameOverInput(&event);
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
