#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/*
    Project: DonCE-Kong-Jr
    Client for the game to connect to the java server.
    Language Standard: C17

    Franco Sagot Lopez - 2022211182
*/

// Definicion de variables sobre la ventana
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// Corre al iniciar la aplicacion
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

    // Metadata de la aplicacion
    SDL_SetAppMetadata("DonCE-Kong-Jr", "1.0", "com.tec.donce-kong-jr");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 512, 448, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 512, 448, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

// Esta es la función que corre cada vez que hay un evento (input de mouse, teclado, etc)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // Termina el programa, reportando exito al SO.
    }
    return SDL_APP_CONTINUE;  // Continua con el programa!
}

// Esta es la función que corre una vez por frame
SDL_AppResult SDL_AppIterate(void *appstate){

    return SDL_APP_CONTINUE;  // Continua con el programa!
}

// Corre al cerrar la aplicacion
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}