# Client-Server Communication Protocol

## Overview

The DonCE-Kong-Jr game uses a client-server architecture where:
- **Server (Java)**: Runs the game logic, physics, and collision detection
- **Client (C)**: Handles rendering and user input

## Connection

- **Protocol**: TCP/IP
- **Port**: 2121
- **Host**: localhost (default)

## Message Flow

### 1. Client → Server (Input Commands)

The client sends text commands when keys are pressed/released:

| Key | Command | Description |
|-----|---------|-------------|
| ← (Left Arrow) | `move_left` | Move player left |
| → (Right Arrow) | `move_right` | Move player right |
| ↑ (Up Arrow) | `climb_up` | Climb up vine or jump |
| ↓ (Down Arrow) | `climb_down` | Climb down vine |
| Space | `jump` | Jump |
| Key Release | `stop` | Stop horizontal movement |

**Format**: Plain text string
**Example**: `move_left`

### 2. Server → Client (Game State)

The server sends the complete game state 20 times per second (50ms interval).

**Format**: `STATE|<gameNum>|PLAYER|<x>,<y>,<lives>,<score>,<state>|ENEMIES|<enemyList>|FRUITS|<fruitList>`

**Example**:
```
STATE|1|PLAYER|100.5,200.0,3,0,walking|ENEMIES|red(25.0,100.0);blue(89.0,80.0)|FRUITS|banana(100,150)
```

#### Field Descriptions:

- **gameNum**: Game instance number (1 or 2)
- **Player Data**:
  - `x, y`: Player position (float)
  - `lives`: Number of lives remaining (int)
  - `score`: Current score (int)
  - `state`: Animation state - `idle`, `walking`, or `climbing`
  
- **Enemy List**: Semicolon-separated enemies
  - Format per enemy: `type(x,y)`
  - Types: `redenemy`, `blueenemy`
  
- **Fruit List**: Semicolon-separated collectibles
  - Format per fruit: `type(x,y)`
  - Types: `banana`, `orange`, `strawberry`

## Implementation Details

### Client Side (C)

**Sending Commands** (`input.c`):
```c
if (isConnected()) {
    const char* command = "move_left";
    sendToServer(command, strlen(command));
}
```

**Receiving State** (`game_logic.c`):
```c
char buffer[4096];
int received = receiveFromServer(buffer, sizeof(buffer));
if (received > 0) {
    parseGameState(buffer);
}
```

**Parsing State**:
1. Split by `|` delimiter
2. Extract player position, lives, score, and state
3. Update local player representation
4. Parse enemy and fruit positions (TODO)

### Server Side (Java)

**Receiving Commands** (`GameClientHandler.java`):
```java
String message = this.input.readUTF();
processCommand(message);
```

**Processing Commands**:
```java
switch (action) {
    case "move_left":
        game.getPlayer().move("left");
        break;
    case "move_right":
        game.getPlayer().move("right");
        break;
    // ... etc
}
```

**Game Loop** (20 FPS):
```java
while (connected) {
    // Update physics
    game.getPlayer().applyGravity();
    game.getPlayer().update();
    
    // Update enemies
    for (Enemy enemy : game.getEnemies()) {
        enemy.patrol();
        enemy.update();
    }
    
    // Check collisions
    game.collisions();
    
    // Send state to client
    sendGameState();
    
    Thread.sleep(50); // 20 updates/second
}
```

**Building State Message**:
```java
StringBuilder gameState = new StringBuilder();
gameState.append("STATE|");
gameState.append(gameNumber).append("|");
gameState.append("PLAYER|");
gameState.append(player.getX()).append(",");
gameState.append(player.getY()).append(",");
gameState.append(player.getLives()).append(",");
gameState.append(player.getScore()).append(",");
gameState.append(player.getState()).append("|");
// ... enemies and fruits
this.output.writeUTF(gameState.toString());
```

## Network Architecture

```
┌─────────────────────────────────────────┐
│           Java Server                   │
│  ┌───────────────────────────────────┐  │
│  │     GameClientHandler Thread      │  │
│  │                                   │  │
│  │  ┌─────────────┐  ┌────────────┐ │  │
│  │  │ Input Thread│  │ Game Loop  │ │  │
│  │  │ (Receive    │  │ (Physics + │ │  │
│  │  │  Commands)  │  │  Send State)│ │  │
│  │  └─────────────┘  └────────────┘ │  │
│  └───────────────────────────────────┘  │
└─────────────────────────────────────────┘
                │         ▲
                │         │
          Commands     State Updates
          (Events)     (20 FPS)
                │         │
                ▼         │
┌─────────────────────────────────────────┐
│            C Client                     │
│  ┌───────────────────────────────────┐  │
│  │  Input Handler   │   Game Logic   │  │
│  │  (Send on event) │ (Receive loop) │  │
│  └───────────────────────────────────┘  │
│  ┌───────────────────────────────────┐  │
│  │          Renderer                 │  │
│  │     (30 FPS - independent)        │  │
│  └───────────────────────────────────┘  │
└─────────────────────────────────────────┘
```

## Key Features

1. **Server Authority**: All game logic runs on the server
2. **Client Prediction**: Client renders at 30 FPS independently of 20 FPS updates
3. **Non-blocking I/O**: Client uses non-blocking sockets to avoid frame drops
4. **Separate Threads**: Server uses separate threads for input and game loop
5. **State Synchronization**: Client position is completely controlled by server

## Testing

### Start Server:
```bash
cd src/server/src
javac game/*.java sockets/*.java App.java
java App
```

### Start Client:
```bash
cd src/client/build
cmake ..
cmake --build .
./main.exe  # or ./main on Linux
```

The client will automatically attempt to connect to `localhost:2121` when you select "Start Game" from the menu.

## Troubleshooting

- **Connection refused**: Make sure the Java server is running first
- **Lag/stuttering**: Check network latency or reduce update rate
- **Position desync**: Server is authoritative - client position is controlled by server updates
- **No movement**: Verify commands are being sent (check SDL logs with `SDL_Log`)

## Future Improvements

- [ ] Add delta compression for state updates
- [ ] Implement client-side prediction for smoother movement
- [ ] Add lag compensation techniques
- [ ] Support spectator mode with read-only state
- [ ] Implement reconnection logic
- [ ] Add authentication/session management
