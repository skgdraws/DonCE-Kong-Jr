#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>

/*
    Project: DonCE-Kong-Jr
    Client for the game to connect to the java server.
    Language Standard: C17

    Franco Sagot Lopez - 2022211182
*/

// Estados del juego
typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_QUIT
} GameState;

// Opciones del menu
typedef enum {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT,
    MENU_COUNT
} MenuOption;

// Definicion de variables sobre la ventana
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static GameState gameState = GAME_STATE_MENU;
static MenuOption selectedOption = MENU_START;

// Funcion para renderizar el menu principal
void renderMenu() {
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

// Funcion para renderizar el juego
void renderGame() {
    // Limpiar pantalla
    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
    SDL_RenderClear(renderer);

    // Pantalla de juego (temporal)
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    SDL_FRect gameRect = {50, 50, 412, 348};
    SDL_RenderFillRect(renderer, &gameRect);

    // Texto de placeholder
    SDL_FRect textRect = {200, 200, 100, 30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &textRect);
}

// Funcion principal de renderizado
void render() {
    if (gameState == GAME_STATE_MENU) {
        renderMenu();
    } else if (gameState == GAME_STATE_PLAYING) {
        renderGame();
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderer);
}

// Funcion para manejar input del menu
void handleMenuInput(SDL_Event *event) {
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

// Funcion para manejar input del juego
void handleGameInput(SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        gameState = GAME_STATE_MENU;
    }
}

// Funcion para procesar eventos
void handleEvents(bool *running) {
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

// Funcion para actualizar la logica del juego
void update() {
    // Aqui ira la logica de actualizacion del juego
    // Por ahora no hay nada que actualizar
}

int main(int argc, char *argv[]) {
    bool running = true;

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
        handleEvents(&running);

        // Actualizar logica del juego
        update();

        // Renderizar
        render();

        // Limitar a ~60 FPS
        SDL_Delay(16);
    }

    // Limpieza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}