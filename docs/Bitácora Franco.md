# Bitácora de Desarrollo - Franco
## Proyecto: DonCE-Kong-Jr

---

## Semana 1 - [10 de Noviembre - 16 de Noviembre]

### Tareas Asignadas
- [x] Configurar entorno de desarrollo con SDL3
- [x] Crear ventana básica del juego
- [x] Configurar CMake para MinGW-x64
- [ ] Implementar renderizado de sprites
- [ ] Diseñar arquitectura del cliente

### Progreso Diario

#### Viernes 15 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Creación de la ventana del juego usando SDL3
- Inicialización del renderer con presentación lógica de 512x448 píxeles
- Implementación del game loop principal con manejo de eventos
- Configuración de límite de ~60 FPS con SDL_Delay(16)
- Corrección de configuración de CMake para trabajar con MinGW-x64
- Limpieza de archivos de build antiguos (configuraciones de Visual Studio)
- Actualización de tareas en CMakeLists.txt para compilador GCC

**Problemas encontrados:**
- CMake estaba configurado para Visual Studio en lugar de MinGW
- Archivos de build .vcxproj y configuraciones de MSVC causaban conflictos
- Múltiples archivos binarios antiguos (Debug/main.exe, .pdb, .dll) generaban confusión

**Soluciones implementadas:**
- Reconfiguración completa de CMake para usar MinGW Makefiles
- Eliminación de 70+ archivos relacionados con configuración de Visual Studio
- Actualización de compiler flags en CMakeLists.txt
- Generación exitosa de main.exe con MinGW-x64

**Aprendizajes:**
- SDL3 utiliza `SDL_CreateWindowAndRenderer()` para inicializar ambos componentes simultáneamente
- `SDL_SetRenderLogicalPresentation()` permite mantener aspecto ratio correcto con letterboxing
- CMake puede generar diferentes tipos de build systems (Visual Studio, MinGW, etc.)
- Importancia de limpiar archivos de build al cambiar de toolchain

**Pendientes para siguiente sesión:**
- Cargar y renderizar sprites/imágenes
- Implementar sistema de assets (imágenes, fuentes, sonidos)
- Crear estructura básica del personaje jugador
- Investigar manejo de input con SDL3

---

## Semana 2 - [17 de Noviembre - 23 de Noviembre]

### Tareas Asignadas
- [x] Implementar renderizado de sprites
- [x] Crear menú principal
- [x] Agregar imagen de fondo
- [x] Implementar movimiento del jugador
- [x] Agregar animaciones del jugador
- [ ] Implementar lógica de enemigos

### Progreso Diario

#### Martes 19 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
- Implementación del menú principal con opciones interactivas
- Sistema de navegación por teclado (flechas arriba/abajo, Enter para seleccionar)
- Agregada imagen de fondo del nivel (bg.bmp - 58KB)
- Implementación de jugador movible con controles WASD
- Sistema básico de colisión y límites de pantalla
- Renderizado de sprites BMP con SDL_LoadBMP y SDL_CreateTextureFromSurface

**Problemas encontrados:**
- Gestión manual de memoria con SDL_FreeSurface después de crear texturas
- Coordenadas del jugador necesitaban limitarse a los bordes de la pantalla
- Integración del menú con el estado del juego

**Soluciones implementadas:**
- Implementación de enum para estados del juego (MENU, PLAYING, GAME_OVER)
- Sistema de máquina de estados para transiciones
- Liberación correcta de recursos SDL después de crear texturas
- Clamp de posición del jugador usando condicionales

**Aprendizajes:**
- SDL_LoadBMP es útil para cargar imágenes BMP sin dependencias adicionales
- Importancia de gestión de memoria en C (FreeSurface después de CreateTexture)
- Uso de enums para manejar estados del juego de forma limpia
- Renderizado de texto básico usando rectángulos coloreados como placeholders

**Pendientes para siguiente sesión:**
- Agregar más sprites de personajes
- Implementar sistema de animación
- Preparar arquitectura para comunicación con servidor

---

#### Sábado 23 de Noviembre, 2025
**Horas trabajadas:** ~2 horas

**Actividades realizadas:**
- Actualización del To Do List con tareas pendientes
- Revisión de arquitectura del proyecto
- Planificación de modularización del código

**Pendientes para siguiente sesión:**
- Refactorizar código en módulos separados
- Agregar todos los sprites del juego
- Implementar sistema de animación completo

---

## Semana 3 - [24 de Noviembre - 30 de Noviembre]

### Tareas Asignadas
- [x] Refactorizar y modularizar el proyecto
- [x] Agregar todos los sprites del juego
- [x] Implementar sistema de animación del jugador
- [x] Crear módulo de networking con sockets
- [x] Inicializar comunicación básica con servidor
- [ ] Implementar protocolo de comunicación completo
- [ ] Sincronizar estado del juego entre cliente y servidor

### Progreso Diario

#### Lunes 25 de Noviembre, 2025
**Horas trabajadas:** ~6 horas

**Actividades realizadas:**
**Sesión Tarde (16:42 - 16:58):**
- Agregados todos los sprites del juego (11 archivos BMP):
  - Personajes: dk-jr.bmp (28KB), dk.bmp (24KB), mario.bmp (5KB)
  - Enemigos: gator-blue.bmp, gator-red.bmp (2KB c/u)
  - Objetos: cage.bmp, fruit.bmp, life-icon.bmp, point-tally.bmp, points.bmp
- Agregada fuente kongtext.ttf (10KB) para UI
- Implementación de sistema de animación por frames para el jugador
- 4 estados de animación: idle, corriendo, saltando, escalando
- Sistema de spritesheet con SDL_Rect para selección de frames
- Timer de animación para controlar velocidad de frames

**Sesión Noche (20:35 - 21:04):**
- Refactorización completa del proyecto en arquitectura modular
- Creación de 10 módulos separados (.h/.c):
  - `assets.c/h`: Gestión de carga de recursos
  - `player.c/h`: Lógica y renderizado del jugador
  - `enemy.c/h`: Sistema de enemigos
  - `game_state.c/h`: Estado global del juego
  - `game_logic.c/h`: Lógica principal del juego
  - `input.c/h`: Manejo de entrada del teclado
  - `renderer.c/h`: Sistema de renderizado
  - `network.c/h`: Comunicación por sockets
- Implementación del módulo de networking:
  - Inicialización de Winsock2 (WSAStartup)
  - Creación de socket TCP (AF_INET, SOCK_STREAM)
  - Función de conexión al servidor
  - Funciones send/receive básicas
  - Manejo de errores con WSAGetLastError()
- Actualización de CMakeLists.txt para compilar todos los módulos
- Enlace con biblioteca ws2_32 para sockets en Windows
- Corrección de inicialización de socket en main.c
- Integración del sistema de red con el game loop

**Problemas encontrados:**
- Código monolítico en main.c (~500 líneas) difícil de mantener
- Falta de separación de responsabilidades
- Inicialización incorrecta de sockets (faltaba WSAStartup antes de socket())
- Error de compilación por falta de enlace con ws2_32.lib
- Gestión de memoria compleja con múltiples recursos SDL

**Soluciones implementadas:**
- Arquitectura modular con separación clara de responsabilidades
- main.c reducido a ~77 líneas (solo inicialización y game loop)
- Cada módulo con responsabilidad única y bien definida
- CMakeLists.txt actualizado con todos los archivos fuente
- Agregado `-lws2_32` a las opciones de enlace
- Corrección del orden de inicialización: WSAStartup → socket() → connect()
- Sistema de asset manager para centralizar carga de recursos
- Structs bien definidas para Player, Enemy, GameState

**Aprendizajes:**
- Arquitectura modular en C requiere cuidadosa gestión de headers y dependencias
- Winsock2 requiere inicialización explícita antes de usar sockets
- CMake necesita listar explícitamente todos los archivos fuente
- Importancia de separar lógica de presentación desde el inicio
- Sockets en Windows requieren enlazar con ws2_32
- SDL_Rect permite implementar spritesheets de forma eficiente
- Forward declarations en headers previenen dependencias circulares

**Pendientes para siguiente sesión:**
- Implementar protocolo de comunicación cliente-servidor
- Definir estructura de mensajes (handshake, input, estado)
- Sincronizar posición del jugador con el servidor
- Implementar lógica de enemigos
- Sistema de colisiones completo
- Manejo de desconexión y reconexión

---

#### Miércoles 26 de Noviembre, 2025
**Horas trabajadas:** ~5 horas

**Actividades realizadas:**
- Implementación casi completa del cliente con nuevas pantallas
- Mejora significativa en la conectividad con el servidor
- Sistema de estados del juego expandido:
  - `GAME_STATE_MENU`: Menú principal
  - `GAME_STATE_CONNECTING`: Pantalla de conexión como jugador
  - `GAME_STATE_CONNECTING_SPECTATE`: Conexión como espectador
  - `GAME_STATE_PLAYING`: Jugando activamente
  - `GAME_STATE_SPECTATING`: Modo espectador
  - `GAME_STATE_SPECTATE`: Selección de juego a observar
- Implementación del protocolo de comunicación:
  - Cliente envía "play" al conectar como jugador
  - Cliente envía "spectate X" para espectar juego X
  - Formato de estado: `STATE|gameNum|PLAYER|data|ENEMIES|data|FRUITS|data`
- Parsing de estado del juego desde el servidor:
  - Posición y estado del jugador (x, y, vidas, puntos)
  - Lista de enemigos con tipo y posición
  - Lista de frutas/coleccionables

**Problemas encontrados:**
- Sincronización de estados entre cliente y servidor
- Formato de mensajes inconsistente
- Manejo de conexiones no bloqueantes

**Soluciones implementadas:**
- Socket configurado como no bloqueante para evitar bloqueos
- Parseo robusto de mensajes con separadores definidos
- Prefijo de longitud de 2 bytes (formato Java writeUTF) para mensajes

**Aprendizajes:**
- Importancia de definir un protocolo de comunicación claro desde el inicio
- Sockets no bloqueantes requieren manejo especial de errores WSAEWOULDBLOCK
- Diseño de máquina de estados facilita gestión de múltiples modos de juego

---

#### Jueves 27 de Noviembre, 2025
**Horas trabajadas:** ~4 horas

**Actividades realizadas:**
**Sesión Tarde (16:37):**
- Correcciones varias en el sistema de comunicación
- Ajustes en el manejo de estados del juego
- Mejoras en la estabilidad de la conexión

**Sesión Noche (18:42):**
- Corrección mayor de errores en todo el sistema:
  - **Fix: Parsing de enemigos y frutas**: Cambio de `%d` a `%f` en sscanf
    - El servidor envía coordenadas como floats (ej: `100.0,50.0`)
    - El cliente intentaba parsear como enteros, causando fallos
  - **Fix: Renderizado de enemigos**: Corrección de índices de frames en spritesheet
  - **Fix: Colección de frutas**: Corrección de `remove(i)` a `remove(i.intValue())`
    - En Java, `ArrayList.remove(Integer)` busca el objeto, no el índice
    - Esto causaba que las frutas dieran puntos infinitos sin desaparecer
- Implementación del patrón Observer para espectadores:
  - Interfaz `GameObserver` con método `onGameStateUpdate(String gameState)`
  - Interfaz `GameSubject` con `addObserver`, `removeObserver`, `notifyObservers`
  - Clase `SpectatorHandler` implementa `GameObserver`
  - Clase `Logic` implementa `GameSubject`
- Separación de lógica de espectadores de `GameClientHandler`
- Espectadores ahora reciben actualizaciones automáticamente vía Observer

**Problemas encontrados:**
- Enemigos y frutas no aparecían en el cliente
- Frutas daban puntos infinitos al recogerlas
- Espectadores no recibían actualizaciones del juego correcto
- `NullPointerException` en clientsIDs del servidor

**Soluciones implementadas:**
- Parsing con floats (`%f`) en lugar de integers (`%d`)
- Uso de `remove(i.intValue())` para eliminar por índice en ArrayList
- Patrón Observer para desacoplar espectadores del handler de jugadores
- Inicialización de `Integer clientsIDs = 0` en lugar de null

**Aprendizajes:**
- Java distingue entre `remove(int index)` y `remove(Object o)` en ArrayList
- El patrón Observer es ideal para notificar múltiples clientes de cambios de estado
- Importancia de consistencia entre formatos de datos cliente-servidor
- Los wrappers de Java (Integer, Double) requieren atención especial con null

---

#### Viernes 28 de Noviembre, 2025
**Horas trabajadas:** ~3 horas

**Actividades realizadas:**
- Finalización del sistema de espectadores con patrón Observer
- Correcciones finales en el parsing de frutas:
  - Asegurar que todas las secciones usen `%f` para coordenadas
- Pruebas de integración cliente-servidor completas
- Verificación de funcionalidad:
  - ✅ Jugadores pueden conectarse y jugar
  - ✅ Espectadores pueden observar juegos en curso
  - ✅ Enemigos se renderizan y mueven correctamente
  - ✅ Frutas aparecen, se recolectan y desaparecen
  - ✅ Puntuación y vidas se sincronizan correctamente
- Documentación del protocolo de comunicación

**Estado final del sistema:**
- Cliente C/SDL3 completamente funcional
- Servidor Java con soporte para múltiples juegos
- Sistema de espectadores usando patrón Observer
- Comunicación bidireccional estable

**Archivos clave modificados:**
- `game_logic.c`: Parsing de estado, conexión, comandos
- `GameClientHandler.java`: Loop del juego, construcción de estado
- `Logic.java`: Implementación de GameSubject, colisiones
- `SpectatorHandler.java`: Implementación de GameObserver
- `Server.java`: Routing de jugadores vs espectadores
- `App.java`: Registro de handlers y observers

---

## Resumen General del Proyecto

### Componentes Desarrollados
- **Cliente (C con SDL3):** 
  - Sistema de renderizado con ventana 512x448
  - Arquitectura modular (10 módulos)
  - Sistema de animación por frames
  - Manejo de input con teclado
  - Módulo de networking con Winsock2
  - Menú principal funcional
  - Movimiento y animación del jugador

- **Servidor (Java):** En desarrollo
- **Manager (C):** Pendiente

### Tecnologías y Librerías Utilizadas
- **SDL3**: Renderizado gráfico, manejo de ventanas, eventos, texturas
- **Winsock2**: Comunicación por sockets TCP en Windows
- **CMake**: Sistema de build con MinGW-x64
- **GCC**: Compilador C (MinGW)
- **Git**: Control de versiones

### Arquitectura del Cliente
**Módulos implementados:**
1. `main.c` - Punto de entrada y game loop principal
2. `assets.c/h` - Gestión de recursos (imágenes, fuentes)
3. `player.c/h` - Lógica del jugador y animaciones
4. `enemy.c/h` - Sistema de enemigos
5. `game_state.c/h` - Estado global del juego
6. `game_logic.c/h` - Lógica principal del juego
7. `input.c/h` - Procesamiento de entrada
8. `renderer.c/h` - Sistema de renderizado
9. `network.c/h` - Comunicación cliente-servidor

### Desafíos Principales
1. **Configuración del entorno de desarrollo**: Migración de Visual Studio a MinGW-x64, limpieza de archivos de configuración conflictivos
2. **Gestión de memoria en C**: Correcta liberación de superficies y texturas SDL
3. **Arquitectura modular**: Refactorización de código monolítico a sistema modular con dependencias claras
4. **Networking en Windows**: Inicialización correcta de Winsock2 y gestión de sockets
5. **Sistema de animación**: Implementación de spritesheets y control de frames

### Logros Destacados
1. ✅ Entorno de desarrollo completamente funcional con SDL3 y CMake
2. ✅ Sistema de renderizado con presentación lógica y letterboxing
3. ✅ Arquitectura modular bien estructurada (main.c reducido de 500 a 77 líneas)
4. ✅ Sistema de animación por frames funcional
5. ✅ Módulo de networking completo con protocolo definido
6. ✅ Todos los sprites del juego integrados (11 archivos)
7. ✅ Menú principal con navegación por teclado
8. ✅ Comunicación cliente-servidor bidireccional funcional
9. ✅ Sistema de espectadores con patrón Observer
10. ✅ Sincronización de jugador, enemigos y frutas
11. ✅ Parsing robusto de mensajes del servidor
12. ✅ Sistema de estados del juego completo (menú, jugando, espectando)

### Conclusiones y Reflexiones
- La modularización temprana es crucial para mantener el código manejable en proyectos C
- SDL3 ofrece una API limpia y potente para desarrollo de juegos 2D
- La gestión manual de memoria en C requiere disciplina y atención constante
- Windows requiere configuración específica para networking (Winsock2, ws2_32.lib)
- La separación de responsabilidades facilita enormemente el debugging y mantenimiento
- El uso de CMake con MinGW proporciona un flujo de trabajo consistente
- La implementación de sistemas de estado simplifica el manejo de la lógica del juego

### Próximos Pasos
1. Pulir la experiencia de usuario (transiciones, feedback visual)
2. Agregar efectos de sonido y música
3. Implementar sistema de niveles progresivos
4. Mejorar IA de enemigos
5. Agregar más tipos de coleccionables
6. Implementar tabla de puntuaciones
7. Optimizar rendimiento de red

---

## Notas Adicionales
- **Total de commits hasta 28/11/2025:** 23+ commits en rama franco-develop-2
- **Líneas de código:** ~2,500+ líneas (cliente C + servidor Java)
- **Assets:** 11 sprites BMP + 1 fuente TTF
- **Tamaño del ejecutable:** ~224 KB (main.exe)
- **Patrones de diseño implementados:** Observer (espectadores), Factory (enemigos/frutas), State (estados del juego)
- **Protocolo de comunicación:** TCP con mensajes formato Java writeUTF (2-byte length prefix)
