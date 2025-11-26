#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "game_state.h"
#include "player.h"
#include "enemy.h"
#include "assets.h"
#include "renderer.h"
#include "input.h"
#include "game_logic.h"
#include "network.h"

/*
╔═══════════════════════════════════════════════════════════════════════════╗
║                          DonCE-Kong-Jr Client                             ║
║                                                                           ║
║  A multiplayer Donkey Kong Jr. game client built with SDL3                ║
║  Connects to Java server for real-time gameplay synchronization           ║
║                                                                           ║
║  Language: C17                                                            ║
║  Author:   Franco Sagot Lopez - 2022211182                                ║
╚═══════════════════════════════════════════════════════════════════════════╝
*/

int main(int argc, char *argv[]) {
    bool running = true;

    // Inicializar generador de numeros aleatorios
    srand((unsigned int)time(NULL));

    // Inicializar sistema de red
    if (!initNetwork()) {
        SDL_Log("Error al inicializar el sistema de red");
        return 1;
    }

    // Metadata de la aplicacion
    SDL_SetAppMetadata("DonCE Kong Jr", "1.0", "com.tec.donce-kong-jr");

    // Inicializar SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    // Crear ventana y renderer
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("DonCE Kong Jr", 512, 448, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("No se pudo crear la ventana/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, 512, 448, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    loadAssets(renderer);

    // Conectar al servidor Java
    if (!connectToServer("localhost", 2021)) {
        SDL_Log("No se pudo conectar al servidor. Continuando en modo local...");
    }

    // Loop principal del juego
    while (running) {
        // Procesar eventos
        handleEvents(&running);

        // Actualizar logica del juego
        update();

        // Renderizar
        render(renderer);

        // Limitar a ~30 FPS
        SDL_Delay(32);
    }

    // Limpieza
    cleanupAssets();
    cleanupNetwork();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}