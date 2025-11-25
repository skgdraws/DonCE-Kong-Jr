#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

// Constantes del jugador
#define PLAYER_SPEED 3.0f
#define PLAYER_SIZE 32.0f
#define PLAYER_SPRITE_WIDTH 32
#define PLAYER_SPRITE_HEIGHT 16
#define ANIMATION_SPEED 8  // Frames antes de cambiar sprite

// Indices de sprites en el spritesheet
#define SPRITE_IDLE_1 1
#define SPRITE_WALK_1 2
#define SPRITE_WALK_2 3
#define SPRITE_WALK_2 4
#define SPRITE_CLIMB_1 7
#define SPRITE_CLIMB_2 8

// Constantes de los enemigos
#define MAX_ENEMIES 10
#define ENEMY_SPEED 2.0f
#define ENEMY_SIZE 24.0f

// Estructura de datos del servidor
typedef struct {
    float x;
    float y;
    const char* state;  // "idle", "walking", "climbing", etc.
} ServerPlayerData;

// Estructura del jugador
typedef struct {
    float x;        // Posicion X en pantalla
    float y;        // Posicion Y en pantalla
    float size;
    int spriteIndex;
    int animCounter;
} Player;

// Estructura del enemigo
typedef struct {
    float x;
    float y;
    float velX;
    float velY;
    float speed;
    float size;
    bool active;
} Enemy;

// Definicion de variables sobre la ventana
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static GameState gameState = GAME_STATE_MENU;
static MenuOption selectedOption = MENU_START;

// Texturas
static SDL_Texture *backgroundTexture = NULL;
static SDL_Texture *playerSpritesheet = NULL;

// Instancia del jugador
static Player player = {
    .x = 230.0f,
    .y = 200.0f,
    .size = PLAYER_SIZE,
    .spriteIndex = SPRITE_IDLE_1,
    .animCounter = 0
};

// Array de enemigos
static Enemy enemies[MAX_ENEMIES] = {0};
static int enemyCount = 0;

// Funcion para generar un enemigo
void spawnEnemy(float x, float y, float velX, float velY) {
    // Buscar un slot libre en el array de enemigos
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].x = x;
            enemies[i].y = y;
            enemies[i].velX = velX;
            enemies[i].velY = velY;
            enemies[i].speed = ENEMY_SPEED;
            enemies[i].size = ENEMY_SIZE;
            enemies[i].active = true;
            enemyCount++;
            SDL_Log("Enemigo spawneado en (%.0f, %.0f)", x, y);
            return;
        }
    }
    SDL_Log("No se puede spawnear enemigo: maximo alcanzado");
}

// Funcion central para actualizar al jugador desde datos del servidor
void updatePlayerFromServer(ServerPlayerData* serverData) {
    // Actualizar posicion directamente desde el servidor
    player.x = serverData->x;
    player.y = serverData->y;
    
    // Determinar sprite base segun el estado del servidor
    int baseSprite;
    bool isMoving = false;
    
    if (strcmp(serverData->state, "walking") == 0) {
        baseSprite = SPRITE_WALK_1;
        isMoving = true;
    } else if (strcmp(serverData->state, "climbing") == 0) {
        baseSprite = SPRITE_CLIMB_1;
        isMoving = true;
    } else if (strcmp(serverData->state, "idle") == 0) {
        baseSprite = SPRITE_IDLE_1;
        isMoving = false;
    } else {
        // Estado desconocido, usar idle por defecto
        baseSprite = SPRITE_IDLE_1;
        isMoving = false;
    }
    
    // Actualizar animacion
    if (isMoving) {
        player.animCounter++;
        if (player.animCounter >= ANIMATION_SPEED) {
            player.animCounter = 0;
            // Alternar entre frame 1 y 2
            if (player.spriteIndex == baseSprite) {
                player.spriteIndex = baseSprite + 1;
            } else {
                player.spriteIndex = baseSprite;
            }
        }
        // Si cambiamos de estado, resetear al primer frame
        if (player.spriteIndex < baseSprite || player.spriteIndex > baseSprite + 1) {
            player.spriteIndex = baseSprite;
            player.animCounter = 0;
        }
    } else {
        player.spriteIndex = baseSprite;
        player.animCounter = 0;
    }
}

// Funcion para actualizar enemigos
void updateEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            // Actualizar posicion
            enemies[i].x += enemies[i].velX;
            enemies[i].y += enemies[i].velY;

            // Desactivar enemigos que salen de la pantalla
            if (enemies[i].x < -enemies[i].size || enemies[i].x > 512 + enemies[i].size ||
                enemies[i].y < -enemies[i].size || enemies[i].y > 448 + enemies[i].size) {
                enemies[i].active = false;
                enemyCount--;
            }
        }
    }
}

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

    // Cargar spritesheet del jugador
    SDL_Surface *playerSurface = SDL_LoadBMP("assets/img/dk-jr.bmp");
    if (playerSurface) {
        playerSpritesheet = SDL_CreateTextureFromSurface(renderer, playerSurface);
        SDL_DestroySurface(playerSurface);
        if (playerSpritesheet) {
            SDL_SetTextureScaleMode(playerSpritesheet, SDL_SCALEMODE_NEAREST);
            SDL_Log("Spritesheet del jugador cargado correctamente");
        } else {
            SDL_Log("Error al crear textura del spritesheet: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Error al cargar spritesheet: %s", SDL_GetError());
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
    if (playerSpritesheet) {
        // Usar el indice de sprite directamente
        SDL_FRect srcRect = {
            player.spriteIndex * PLAYER_SPRITE_WIDTH,
            0,
            PLAYER_SPRITE_WIDTH,
            PLAYER_SPRITE_HEIGHT
        };
        SDL_FRect dstRect = {
            player.x,
            player.y,
            PLAYER_SPRITE_WIDTH * 2,  // Escalar 2x
            PLAYER_SPRITE_HEIGHT * 2
        };
        SDL_RenderTexture(renderer, playerSpritesheet, &srcRect, &dstRect);
    } else {
        // Fallback: dibujar rectangulo si no hay sprite
        SDL_FRect playerRect = {player.x, player.y, player.size, player.size};
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

// Funcion para manejar input del juego (solo envia comandos al servidor)
void handleGameInput(SDL_Event *event) {
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
        // TODO: Recibir datos del servidor
        // Por ahora, simulamos datos del servidor para testing local
        ServerPlayerData serverData = {
            .x = player.x,  // Mantener posicion actual (sera reemplazado por datos del servidor)
            .y = player.y,
            .state = "idle"  // Estado por defecto (sera reemplazado por datos del servidor)
        };
        
        // Actualizar jugador con datos del servidor
        updatePlayerFromServer(&serverData);

        // Actualizar enemigos
        updateEnemies();
    }
}

int main(int argc, char *argv[]) {
    bool running = true;

    // Inicializar generador de numeros aleatorios
    srand((unsigned int)time(NULL));

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
    if (playerSpritesheet) {
        SDL_DestroyTexture(playerSpritesheet);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}