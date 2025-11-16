#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>

/*
    Project: DonCE-Kong-Jr
    Client for the game to connect to the java server.
    Language Standard: C17

    Franco Sagot Lopez - 2022211182
*/

// Definicion de variables sobre la ventana
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[]) {
    bool running = true;
    SDL_Event event;

    // Metadata de la aplicacion
    SDL_SetAppMetadata("DonCE Kong Jr", "1.0", "com.tec.donce-kong-jr");

    // Inicializar SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return 1;
    }

    // Crear ventana y renderer
    if (!SDL_CreateWindowAndRenderer("DonCE-Kong-Jr", 512, 448, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("No se pudo crear la ventana/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, 512, 448, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // Loop principal del juego
    while (running) {
        // Procesar eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Limpiar pantalla con color negro
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Aquí irá el código de renderizado del juego

        // Presentar el frame
        SDL_RenderPresent(renderer);

        // Limitar a ~60 FPS
        SDL_Delay(16);
    }

    // Limpieza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}