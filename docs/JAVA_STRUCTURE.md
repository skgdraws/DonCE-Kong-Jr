# Estructura de Paquetes y Clases - DonCE-Kong-Jr Server

## Arquitectura General

```
src/server/src/
│
├── App.java                          # Clase principal del servidor
│
├── game/                             # Paquete de lógica del juego
│   ├── Entity.java                   # [ABSTRACTA] Clase base para entidades
│   │
│   ├── Player.java                   # Jugador (hereda de Entity)
│   │
│   ├── Enemy.java                    # [ABSTRACTA] Enemigo base
│   │   ├── RedEnemy.java            # Enemigo rojo (patrulla verticalmente)
│   │   └── BlueEnemy.java           # Enemigo azul (cae con gravedad)
│   │
│   ├── Collectible.java             # Coleccionable base
│   │   ├── Banana.java              # Banano (100 puntos)
│   │   ├── Orange.java              # Naranja (50 puntos)
│   │   └── Strawberry.java          # Fresa (10 puntos)
│   │
│   ├── Platform.java                # Plataforma del mapa
│   ├── Vine.java                    # Enredadera escalable
│   │
│   ├── EnemyFactory.java            # [ABSTRACTA] Factory de enemigos
│   │   ├── RedFactory.java          # Crea RedEnemy
│   │   └── BlueFactory.java         # Crea BlueEnemy
│   │
│   ├── CollectibleFactory.java      # [ABSTRACTA] Factory de coleccionables
│   │   ├── BananaFactory.java       # Crea Banana
│   │   ├── OrangeFactory.java       # Crea Orange
│   │   └── StrawberryFactory.java   # Crea Strawberry
│   │
│   └── Logic.java                   # Motor del juego
│
└── sockets/                          # Paquete de red
    ├── Server.java                   # Servidor TCP/IP principal
    ├── GameClientHandler.java        # Maneja cliente específico
    ├── ClientListener.java           # Listener genérico (legacy)
    ├── Client.java                   # Cliente de prueba
    ├── Listener.java                 # Utilidad para recibir mensajes
    └── Sender.java                   # Utilidad para enviar mensajes
```

---

## Descripción Detallada de Clases

### Paquete `game`

#### **Entity.java** (Abstracta)
```java
package game;

public abstract class Entity {
    // Atributos
    protected double x, y;           // Posición
    protected double vx, vy;         // Velocidad
    protected int width, height;     // Dimensiones
    
    // Métodos
    + void update()                  // Actualiza posición
    + Rectangle getBounds()          // Obtiene rectángulo de colisión
    + getters para x, y, width, height
}
```

#### **Player.java**
```java
package game;

public class Player extends Entity {
    // Atributos adicionales
    protected int lives;             // Vidas del jugador
    protected int score;             // Puntuación
    protected boolean onGround;      // ¿Está en el suelo?
    protected boolean climbing;      // ¿Está escalando?
    
    // Métodos
    + void applyGravity()           // Aplica física de gravedad
    + void jump()                   // Saltar
    + void stop()                   // Detener movimiento
    + void move(String direction)   // Mover en dirección
    + int getLives()
    + int getScore()
}
```

#### **Enemy.java** (Abstracta)
```java
package game;

public abstract class Enemy extends Entity {
    // Atributos
    protected Vine vine;            // Enredadera asociada
    
    // Métodos
    + void place(Vine vine)         // Colocar en enredadera
    + void setLevel(int level)      // Ajustar velocidad por nivel
    + abstract void patrol()        // Patrullar (implementado por subclases)
}
```

#### **RedEnemy.java**
```java
package game;

public class RedEnemy extends Enemy {
    // Comportamiento: Patrulla arriba-abajo en enredadera
    @Override
    public void patrol() {
        // Invierte dirección al llegar a límites de vine
    }
}
```

#### **BlueEnemy.java**
```java
package game;

public class BlueEnemy extends Enemy {
    // Comportamiento: Cae con gravedad desde enredadera
    @Override
    public void patrol() {
        // Aplica gravedad cuando sale de vine
    }
}
```

#### **Collectible.java**
```java
package game;

public class Collectible extends Entity {
    // Atributos
    protected int value;            // Valor en puntos
    
    // Métodos
    + void place(int x, int y)      // Colocar en posición
}
```

#### **Banana.java, Orange.java, Strawberry.java**
```java
package game;

// Subclases de Collectible con diferentes valores
// Banana: 100 puntos
// Orange: 50 puntos
// Strawberry: 10 puntos
```

#### **Platform.java**
```java
package game;

public class Platform extends Entity {
    // Constructor con posición y dimensiones fijas
    + Platform(int x, int y, int width, int height)
}
```

#### **Vine.java**
```java
package game;

public class Vine extends Entity {
    // Constructor con posición y dimensiones fijas
    + Vine(int x, int y, int width, int height)
}
```

#### **EnemyFactory.java** (Abstracta)
```java
package game;

public abstract class EnemyFactory {
    + abstract Enemy createEnemy()
}
```

#### **RedFactory.java, BlueFactory.java**
```java
package game;

// Implementaciones concretas del patrón Factory
// RedFactory crea RedEnemy
// BlueFactory crea BlueEnemy
```

#### **CollectibleFactory.java** (Abstracta)
```java
package game;

public abstract class CollectibleFactory {
    + abstract Collectible createCollectible()
}
```

#### **BananaFactory.java, OrangeFactory.java, StrawberryFactory.java**
```java
package game;

// Implementaciones concretas del patrón Factory
// Cada factory crea su tipo de coleccionable
```

#### **Logic.java** (Motor del Juego)
```java
package game;

public class Logic {
    // Atributos
    - int level
    - Player player
    - ArrayList<Platform> platforms
    - ArrayList<Vine> vines
    - ArrayList<Collectible> collectibles
    - ArrayList<Enemy> enemies
    - Rectangle Boss, Goal
    
    // Métodos principales
    + Logic(int level)              // Constructor
    + void setMap()                 // Inicializa mapa
    + void setPlayer()              // Posiciona jugador
    + void run()                    // Loop principal
    + void collisions()             // Detección de colisiones
    + void placeEnemy(factory, vine)
    + void placeCollectible(factory, x, y)
    + Player getPlayer()
    + ArrayList<Enemy> getEnemies()
    + ArrayList<Collectible> getCollectibles()
}
```

---

### Paquete `sockets`

#### **Server.java**
```java
package sockets;

public class Server {
    // Atributos
    - ServerSocket server
    - ArrayList<Socket> clients
    - ArrayList<GameClientHandler> handlers
    - int clientsIDs
    - ClientRegistrar registrar
    
    // Interface interna
    + interface ClientRegistrar {
        void registerClientHandler(GameClientHandler handler)
    }
    
    // Métodos
    + void runServer()              // Inicia servidor en puerto 2121
    + void newClient()              // Acepta nuevos clientes
    + void assignID(Socket client)  // Asigna ID único
    + void setClientRegistrar(ClientRegistrar)
}
```

#### **GameClientHandler.java** (Runnable)
```java
package sockets;

public class GameClientHandler implements Runnable {
    // Atributos
    - Socket client
    - DataOutputStream output
    - DataInputStream input
    - Logic game
    - int gameNumber
    - boolean connected
    
    // Métodos
    + GameClientHandler(Socket client)
    + void setGame(Logic game)
    + void setGameNumber(int gameNumber)
    + boolean isConnected()
    + void close()
    - void sendGameState()          // Envía estado al cliente
    - String buildEnemiesList()     // Serializa enemigos
    - String buildFruitsList()      // Serializa frutas
    + void run()                    // Hilo de comunicación
}
```

#### **Client.java**
```java
package sockets;

public class Client {
    // Cliente de prueba para conectarse al servidor
    - Socket socket
    - String id
    - Listener reader
    - Sender sender
    
    + Client(String tag)
    + void joinServer()
    + void startClient()
    + void getID()
}
```

#### **Listener.java**
```java
package sockets;

public class Listener {
    // Utilidad para leer mensajes
    - DataInputStream input
    
    + Listener(DataInputStream input)
    + String receive()
}
```

#### **Sender.java**
```java
package sockets;

public class Sender {
    // Utilidad para enviar mensajes
    - DataOutputStream output
    
    + Sender(DataOutputStream output)
    + void send(String message)
}
```

#### **ClientListener.java** (Runnable) [Legacy]
```java
package sockets;

// Listener genérico para clientes
// Nota: Reemplazado por GameClientHandler para juegos
```

---

### Clase Principal

#### **App.java**
```java
import game.*;
import sockets.*;

public class App implements Server.ClientRegistrar {
    // Atributos
    - Logic game1, game2            // Dos instancias de juego
    - Scanner scanner
    - boolean running
    - Server server
    - GameClientHandler handler1, handler2
    
    // Métodos
    + App()                         // Constructor
    + void start()                  // Inicia servidor y CLI
    - void commandLoop()            // Loop de comandos
    - void handleCreateEnemy(String[])
    - void handleCreateFruit(String[])
    - void handleStatus()
    + void registerClientHandler(GameClientHandler)
    - void handleExit()
    + static void main(String[])    // Punto de entrada
}
```

---

## Relaciones entre Clases

### Herencia
```
Entity
├── Player
├── Enemy
│   ├── RedEnemy
│   └── BlueEnemy
├── Collectible
│   ├── Banana
│   ├── Orange
│   └── Strawberry
├── Platform
└── Vine

EnemyFactory
├── RedFactory
└── BlueFactory

CollectibleFactory
├── BananaFactory
├── OrangeFactory
└── StrawberryFactory
```

### Composición / Agregación
- **Logic** contiene: Player, ArrayList<Enemy>, ArrayList<Collectible>, ArrayList<Platform>, ArrayList<Vine>
- **App** contiene: 2 Logic, Server, 2 GameClientHandler
- **Server** contiene: ArrayList<GameClientHandler>
- **Client** contiene: Listener, Sender
- **Enemy** usa: Vine

### Dependencias
- **Factories** crean sus respectivas entidades
- **GameClientHandler** usa Logic para obtener estado
- **App** implementa Server.ClientRegistrar

---

## Patrones de Diseño Implementados

### 1. **Factory Method**
- **EnemyFactory** y sus subclases (RedFactory, BlueFactory)
- **CollectibleFactory** y sus subclases (BananaFactory, OrangeFactory, StrawberryFactory)
- Permite crear objetos sin especificar su clase exacta

### 2. **Strategy**
- **Enemy.patrol()** es abstracto, cada tipo de enemigo implementa su estrategia de patrullaje
- RedEnemy: patrulla vertical
- BlueEnemy: cae con gravedad

### 3. **Observer**
- **Server.ClientRegistrar** interface permite desacoplar Server de App
- App "observa" cuando hay nuevos clientes

### 4. **Singleton** (implícito)
- **App** maneja dos instancias únicas de Logic (game1, game2)

---

## Diagrama de Flujo de Ejecución

```
1. App.main()
   └─> App.start()
       ├─> Server.runServer() [Hilo separado]
       │   └─> Acepta clientes en loop
       │       └─> Crea GameClientHandler
       │           └─> App.registerClientHandler()
       │               └─> Asigna a game1 o game2
       │
       └─> commandLoop()
           └─> Procesa comandos del administrador
               ├─> create_enemy
               ├─> create_fruit
               ├─> status
               └─> exit
```

---

## Comandos de Administración

### Crear Enemigo
```bash
create_enemy <game> <type> <vine>
# game: 1 o 2
# type: red, blue
# vine: índice de enredadera (0-13)

# Ejemplo:
create_enemy 1 red 5
```

### Crear Fruta
```bash
create_fruit <game> <type> <x> <y>
# game: 1 o 2
# type: banana, orange, strawberry
# x, y: coordenadas

# Ejemplo:
create_fruit 1 banana 100 150
```

### Ver Estado
```bash
status
# Muestra estado de game1 y game2
```

### Salir
```bash
exit
```

---

## Protocolo de Comunicación

### Formato del Estado del Juego
```
STATE|<gameNumber>|PLAYER|<x>,<y>,<lives>,<score>|ENEMIES|<enemyList>|FRUITS|<fruitList>
```

### Ejemplo
```
STATE|1|PLAYER|6.0,224.0,3,0|ENEMIES|red(25.0,100.0);blue(89.0,80.0)|FRUITS|banana(100,150);orange(50,200)
```

---

## Checklist de Implementación

- [x] Entity (clase base abstracta)
- [x] Player (con física y movimiento)
- [x] Enemy (abstracta con patrol)
- [x] RedEnemy, BlueEnemy (comportamientos específicos)
- [x] Collectible (clase base)
- [x] Banana, Orange, Strawberry (valores específicos)
- [x] Platform, Vine (estructuras del mapa)
- [x] EnemyFactory y subclases
- [x] CollectibleFactory y subclases
- [x] Logic (motor del juego)
- [x] Server (servidor TCP/IP)
- [x] GameClientHandler (comunicación por juego)
- [x] Client, Listener, Sender (utilidades)
- [x] App (aplicación principal con CLI)

---

## Compilación y Ejecución

### Compilar
```bash
cd src/server/src
javac -d ../bin App.java game/*.java sockets/*.java
```

### Ejecutar Servidor
```bash
cd src/server/bin
java App
```

### Ejecutar Cliente de Prueba
```bash
java sockets.Client
```

---

## Notas de Implementación

1. **Multithreading**: El servidor usa hilos para manejar múltiples clientes simultáneamente
2. **Factory Pattern**: Facilita la creación dinámica de enemigos y coleccionables en tiempo de ejecución
3. **Separación de Responsabilidades**: game/ maneja lógica, sockets/ maneja red, App coordina todo
4. **Escalabilidad**: Fácil agregar nuevos tipos de enemigos o coleccionables creando nuevas factories

---

**Generado automáticamente para DonCE-Kong-Jr**
*Fecha: 27 de noviembre de 2025*
