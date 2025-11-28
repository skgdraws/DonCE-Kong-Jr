<div align="center">

# 🎮 DonCE-Kong-Jr

<img src="https://img.shields.io/badge/Language-C%20%7C%20Java-blue.svg" alt="Language">
<img src="https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg" alt="Platform">
<img src="https://img.shields.io/badge/Architecture-Client--Server-orange.svg" alt="Architecture">
<img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">

**Un juego multijugador inspirado en el clásico Donkey Kong Jr. con arquitectura híbrida C/Java**

[Características](#-características) •
[Arquitectura](#-arquitectura) •
[Instalación](#-instalación) •
[Uso](#-uso) •
[Documentación](#-documentación)

</div>

---

## 📖 Descripción

DonCE-Kong-Jr es un juego multijugador inspirado en el clásico Donkey Kong Jr. con arquitectura cliente-servidor híbrida. El servidor está implementado en **Java** para aprovechar su robustez en aplicaciones de red y manejo de múltiples clientes, mientras que el cliente está desarrollado en **C con SDL3** para un renderizado gráfico eficiente y control directo del hardware. El proyecto demuestra comunicación mediante sockets TCP/IP, arquitectura modular, y sistemas distribuidos multi-lenguaje.

## ✨ Características

- 🎯 **Arquitectura Cliente-Servidor**: Comunicación mediante sockets TCP/IP (puerto 2121)
- 👥 **Multijugador**: Soporte para 2 juegos simultáneos con múltiples espectadores
- 👁️ **Modo Espectador**: Observa partidas en curso usando el patrón Observer
- 🎨 **Renderizado con SDL3**: Ventana 512x448 con presentación lógica y letterboxing
- 🎮 **Sistema de Animación**: Frames animados para personajes (idle, corriendo, saltando, escalando)
- 👾 **Enemigos Dinámicos**: Cocodrilos rojos y azules con IA de patrulla
- 🍎 **Frutas Coleccionables**: Naranjas, bananas y fresas con sistema de puntuación
- 🏗️ **Arquitectura Modular**: Cliente dividido en 10 módulos independientes
- 🌐 **Networking Asíncrono**: Sockets no bloqueantes con Winsock2
- 📊 **Menú Principal**: Sistema de navegación por teclado con opciones de jugar/espectar
- 🔄 **Reset Automático**: Las salas se reinician cuando un jugador se desconecta
- 🎨 **Assets Completos**: 11 sprites BMP + fuente personalizada Kong Text

## 🏗️ Arquitectura

El proyecto está dividido en tres componentes principales:

```
DonCE-Kong-Jr/
│
├── src/
│   ├── client/          # Cliente del juego (C + SDL3)
│   │   ├── src/         # Código fuente modular
│   │   │   ├── main.c           # Punto de entrada y game loop
│   │   │   ├── assets.c/h       # Gestión de recursos
│   │   │   ├── player.c/h       # Lógica del jugador
│   │   │   ├── enemy.c/h        # Sistema de enemigos
│   │   │   ├── game_state.c/h   # Estado del juego
│   │   │   ├── game_logic.c/h   # Lógica principal
│   │   │   ├── input.c/h        # Manejo de entrada
│   │   │   ├── renderer.c/h     # Sistema de renderizado
│   │   │   └── network.c/h      # Comunicación con servidor
│   │   ├── assets/
│   │   │   ├── img/             # Sprites (11 archivos BMP)
│   │   │   └── font/            # Fuente Kong Text TTF
│   │   ├── build/               # Archivos generados por CMake
│   │   └── CMakeLists.txt       # Configuración de build
│   │
│   └── server/          # Servidor del juego (Java)
│       └── src/
│           ├── App.java              # Aplicación principal
│           ├── game/                 # Lógica del juego
│           │   ├── Logic.java        # Lógica principal + GameSubject
│           │   ├── Player.java       # Entidad jugador
│           │   ├── Enemy.java        # Clase base enemigos
│           │   ├── RedEnemy.java     # Cocodrilo rojo
│           │   ├── BlueEnemy.java    # Cocodrilo azul
│           │   ├── EnemyFactory.java # Factory para enemigos
│           │   ├── Entity.java       # Clase base
│           │   ├── Platform.java     # Plataformas
│           │   ├── Vine.java         # Enredaderas
│           │   ├── Collectible.java  # Clase base coleccionables
│           │   ├── Orange.java       # Naranja
│           │   ├── Banana.java       # Banana
│           │   ├── Strawberry.java   # Fresa
│           │   ├── CollectibleFactory.java # Factory para frutas
│           │   ├── GameObserver.java # Interfaz Observer
│           │   └── GameSubject.java  # Interfaz Subject
│           └── sockets/              # Sistema de red
│               ├── Server.java       # Servidor TCP
│               ├── GameClientHandler.java # Handler de jugadores
│               ├── SpectatorHandler.java  # Handler de espectadores
│               └── Client.java
│
└── docs/               # Documentación del proyecto
    ├── Bitácora Franco.md
    ├── Bitácora Kevin.md
## 🚀 Instalación

### Prerrequisitos

**Para el Cliente (C):**
- **CMake** 3.20 o superior
- **MinGW-x64** (GCC para Windows) o GCC en Linux
- **SDL3** (Simple DirectMedia Layer 3)
- **Winsock2** (Windows) o sockets POSIX (Linux)

**Para el Servidor (Java):**
- **JDK 11** o superior
- IntelliJ IDEA (recomendado) o cualquier IDE Java

### Windows

#### Cliente

```powershell
# Clonar el repositorio
git clone https://github.com/skgdraws/DonCE-Kong-Jr.git
cd DonCE-Kong-Jr/src/client

# Configurar y compilar con CMake
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

# El ejecutable estará en: src/client/main.exe
```

#### Servidor

```powershell
# Desde IntelliJ IDEA
# 1. Abrir el proyecto: src/server
# 2. Ejecutar App.java

# O desde terminal
cd src/server/src
javac App.java game/*.java sockets/*.java
java App
```

### Linux

```bash
# Cliente
cd src/client
mkdir build && cd build
cmake ..
make

# Servidor
cd src/server/src
javac App.java game/*.java sockets/*.java
java App
```

## 🎮 Uso

### Iniciar el Servidor (Java)

```bash
# Desde src/server/src
java App

# El servidor iniciará en el puerto 2121
# Salida esperada:
# === Donkey Kong Jr - Multi-Game Server ===
# Starting server on port 2121...
```

### Iniciar el Cliente (C)

```bash
# Windows
cd src/client
.\main.exe

# Linux
cd src/client/build
./main

# El cliente intentará conectarse automáticamente a localhost:2121
```

### Ejemplo de Sesión Completa

```bash
# Terminal 1 - Iniciar servidor (Java)
cd src/server/src
java App
# Comandos disponibles en el servidor:
#   create_enemy <game> <type> <vine>  - Crear enemigo (type: red, blue)
#   create_fruit <game> <type> <vine> <y> <value> - Crear fruta
#   status - Ver estado de los juegos
#   exit - Salir

# Terminal 2 - Iniciar cliente 1 como jugador
cd src/client
.\main.exe
# Seleccionar "Play" en el menú

# Terminal 3 - Iniciar cliente 2 como espectador
cd src/client
.\main.exe
# Seleccionar "Spectate Game 1" para observar
```

## 🎯 Controles del Juego

### Menú Principal
- **↑/↓**: Navegar opciones
- **Enter**: Seleccionar opción
- **Opciones**: Jugar, Espectar Juego 1, Espectar Juego 2

### En Juego
- **W/↑**: Subir / Escalar
- **A/←**: Mover izquierda
- **S/↓**: Bajar / Descender
- **D/→**: Mover derecha
- **Espacio**: Saltar
- **ESC**: Volver al menú

### Modo Espectador
- **ESC**: Desconectarse y volver al menú

## 📚 Documentación

Para más detalles sobre el desarrollo del proyecto, consulta las bitácoras:

- [Bitácora Franco Sagot](docs/Bitácora%20Franco.md)
- [Bitácora Kevin Ruiz](docs/Bitácora%20Kevin.md)
- [Bitácora Pamela Chacón](docs/Bitácora%20Pamela.md)

### Tecnologías Utilizadas

**Cliente:**
- SDL3 (Simple DirectMedia Layer 3)
- Winsock2 / POSIX Sockets
- CMake + MinGW-x64
- C17

**Servidor:**
- Java 11+
- ServerSocket (java.net)
- Multithreading
- Factory Pattern para entidades
- Observer Pattern para espectadores

## 🛠️ Desarrollo

### Arquitectura del Cliente

El cliente está modularizado en componentes independientes:

- **main.c**: Game loop principal (~60 FPS)
- **network.c/h**: Comunicación TCP/IP asíncrona
- **renderer.c/h**: Renderizado con SDL3
- **player.c/h**: Lógica y animación del jugador
- **enemy.c/h**: Sistema de enemigos
- **game_state.c/h**: Estado global del juego
- **game_logic.c/h**: Lógica principal
- **input.c/h**: Procesamiento de entrada
- **assets.c/h**: Gestión de recursos

### Estructura de Comunicación

- **Protocolo**: TCP/IP con formato Java writeUTF (2-byte length prefix)
- **Puerto**: 2121
- **Formato de Estado**: `STATE|gameNum|PLAYER|x,y,lives,score,state|ENEMIES|list|FRUITS|list`
- **Comandos Cliente→Servidor**: `play`, `spectate X`, `move_left`, `move_right`, `jump`, `climb_up`, `climb_down`, `stop`
- **Cliente**: Sockets no bloqueantes (FIONBIO)
- **Servidor**: Multithreading con GameClientHandler por jugador, SpectatorHandler por espectador

### Compilación en Modo Debug

```bash
# Cliente (CMake)
cd src/client/build
cmake -DCMAKE_BUILD_TYPE=Debug ..
mingw32-make

# Servidor Java
javac -g App.java game/*.java sockets/*.java
```

### Limpieza

```bash
# Cliente
cd src/client/build
mingw32-make clean

# Servidor
cd src/server/src
del /Q *.class game\*.class sockets\*.class  # Windows
rm *.class game/*.class sockets/*.class      # Linux
```

### Estructura de Assets

```
src/client/assets/
├── img/
│   ├── bg.bmp              # Fondo (58 KB)
│   ├── dk-jr.bmp           # Donkey Kong Jr (28 KB)
│   ├── dk.bmp              # Donkey Kong (24 KB)
│   ├── mario.bmp           # Mario (5 KB)
│   ├── gator-blue.bmp      # Cocodrilo azul (2 KB)
│   ├── gator-red.bmp       # Cocodrilo rojo (2 KB)
│   ├── cage.bmp            # Jaula (6 KB)
│   ├── fruit.bmp           # Frutas (3 KB)
│   ├── life-icon.bmp       # Icono de vida (1 KB)
│   ├── point-tally.bmp     # Contador (7 KB)
│   └── points.bmp          # Puntos (2 KB)
└── font/
    └── kongtext.ttf        # Fuente Kong Text (10 KB)
```

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto fue desarrollado con fines educativos.

## 👥 Autores

- **Pamela Chacón** - Cliente C - [@PamelaChB](https://github.com/pamelachb)
- **Franco Sagot** - Cliente C + SDL3 - [@SKGDraws](https://github.com/skgdraws)
- **Kevin Ruiz** - Servidor Java - [@Kevrr](https://github.com/kevrr)

## 🙏 Agradecimientos

- Inspirado en el clásico Donkey Kong Jr. de Nintendo (1982)
- SDL3 Team por la excelente biblioteca de renderizado
- Desarrollado como proyecto académico del curso de Paradigmas de Programación
- Instituto Tecnológico de Costa Rica (TEC)

## 📊 Estado del Proyecto

**Versión Actual**: 1.0.0 (Funcional)

**Completado:**
- ✅ Configuración del entorno de desarrollo
- ✅ Sistema de renderizado con SDL3
- ✅ Arquitectura modular del cliente (10 módulos)
- ✅ Sistema de animación por frames
- ✅ Menú principal funcional con opciones de jugar/espectar
- ✅ Módulo de networking completo con protocolo definido
- ✅ Servidor Java con manejo de 2 juegos simultáneos
- ✅ Protocolo de comunicación cliente-servidor bidireccional
- ✅ Sincronización de estado del juego (jugador, enemigos, frutas)
- ✅ Sistema de enemigos con IA de patrulla
- ✅ Sistema de colisiones (plataformas, lianas, enemigos, frutas)
- ✅ Sistema de puntuación y vidas
- ✅ Modo espectador con patrón Observer
- ✅ Reset automático de salas al desconectarse

**Pendiente:**
- ⏳ Niveles adicionales
- ⏳ Sistema de sonido
- ⏳ Efectos visuales
- ⏳ Pantalla de game over
- ⏳ Ranking de jugadores

---

<div align="center">
Made with ❤️ for learning purposes
</div>