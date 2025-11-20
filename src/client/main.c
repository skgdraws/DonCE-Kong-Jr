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

// Texturas
static SDL_Texture *backgroundTexture = NULL;

// Variables del bloque jugador
static float playerX = 230.0f;
static float playerY = 200.0f;
static float playerVelX = 0.0f;
static float playerVelY = 0.0f;
static const float PLAYER_SPEED = 3.0f;
static const float PLAYER_SIZE = 32.0f;

void loadAssets() {
    // Establecer filtro de escalado a nearest neighbor para pixeles nitidos
    SDL_SetHint("SDL_RENDER_SCALE_QUALITY", "0");

    // Cargar imagen de fondo
    SDL_Surface *bgSurface = SDL_LoadBMP("assets/img/bg.bmp");
    if (bgSurface) {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_DestroySurface(bgSurface);
        if (backgroundTexture) {
            // Configurar filtro nearest neighbor para la textura
            SDL_SetTextureScaleMode(backgroundTexture, SDL_SCALEMODE_NEAREST);
            SDL_Log("Fondo cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del fondo: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar fondo: %s", SDL_GetError());
    }
}

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

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
    SDL_FRect playerRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    SDL_RenderFillRect(renderer, &playerRect);
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
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
                gameState = GAME_STATE_MENU;
                break;
            case SDLK_W:
            case SDLK_UP:
                playerVelY = -PLAYER_SPEED;
                break;
            case SDLK_S:
            case SDLK_DOWN:
                playerVelY = PLAYER_SPEED;
                break;
            case SDLK_A:
            case SDLK_LEFT:
                playerVelX = -PLAYER_SPEED;
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                playerVelX = PLAYER_SPEED;
                break;
        }
    } else if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.key) {
            case SDLK_W:
            case SDLK_UP:
                if (playerVelY < 0) playerVelY = 0;
                break;
            case SDLK_S:
            case SDLK_DOWN:
                if (playerVelY > 0) playerVelY = 0;
                break;
            case SDLK_A:
            case SDLK_LEFT:
                if (playerVelX < 0) playerVelX = 0;
                break;
            case SDLK_D:
            case SDLK_RIGHT:
                if (playerVelX > 0) playerVelX = 0;
                break;
        }
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
    // Solo actualizar si estamos jugando
    if (gameState == GAME_STATE_PLAYING) {
        // Actualizar posicion del jugador
        playerX += playerVelX;
        playerY += playerVelY;

        // Mantener al jugador dentro de los limites
        if (playerX < 0) playerX = 0;
        if (playerY < 0) playerY = 0;
        if (playerX > 512 - PLAYER_SIZE) playerX = 512 - PLAYER_SIZE;
        if (playerY > 448 - PLAYER_SIZE) playerY = 448 - PLAYER_SIZE;
    }
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
    if (!SDL_CreateWindowAndRenderer("DonCE Kong Jr", 512, 448, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("No se pudo crear la ventana/renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, 512, 448, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    loadAssets();

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
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}