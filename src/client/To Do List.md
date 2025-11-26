# DonCE Kong Jr - Development To-Do List
**Project:** Client for game to connect to Java server  
**Developer:** Franco Sagot Lopez - 2022211182  
**Language:** C17 with SDL3

---

## 🎯 Window Setup & Initialization
- [x] Initialize SDL3 (video, audio, events)
- [x] Create game window with proper dimensions
- [x] Set up SDL renderer
- [ ] Implement window icon
- [x] Add window title
- [x] Implement proper SDL cleanup on exit

## 🎮 Main Game Loop
- [x] Create main event loop
- [x] Implement frame rate limiting (target FPS)
- [x] Handle quit events (window close, ESC key)
- [x] Set up game state system (menu, playing, etc.)

## 📝 Main Menu UI
- [x] Design main menu layout
- [x] Load and render menu background
- [ ] Load font for menu text (from `assets/font/`)
- [x] Create menu buttons:
  - [x] Start Game
  - [ ] Options/Settings
  - [x] Exit
- [x] Implement button hover effects
- [ ] Add button click detection
- [x] Implement keyboard navigation (arrow keys, Enter)
- [ ] Add menu selection sound effects

## 🎨 Graphics & Rendering
- [x] Load background image (from `assets/img/`)
- [x] Implement texture loading system
- [ ] Create text rendering function
- [x] Add menu logo/title graphic (placeholder)
- [x] Implement basic color schemes
- [x] Set up nearest neighbor filtering for pixel art
- [x] Separate rendering into functions (renderMenu, renderGame, render)

## 🎮 Gameplay
- [x] Create player entity with struct
- [x] Implement server-controlled player movement
- [x] Add collision with screen boundaries
- [x] Separate game logic into update function
- [x] Add player spritesheet with animations
- [x] Implement sprite index-based animation system
- [x] Encapsulate player attributes in struct
- [x] Enemy spawning system (debug mode with E key)
- [ ] Implement jumping mechanics
- [ ] Add platforms/level geometry
- [ ] Implement collision detection (player-enemy)

## 🔊 Audio for Menu
- [ ] Initialize SDL audio system
- [ ] Load menu background music (from `assets/sound/`)
- [ ] Load button hover/click sound effects
- [ ] Implement audio playback controls
- [ ] Add volume control (music and SFX)

## 🔧 Code Structure
- [x] Create header files:
  - [x] `game_state.h` - Game state management
  - [x] `player.h` - Player logic
  - [x] `enemy.h` - Enemy system
  - [x] `assets.h` - Asset loading/management
  - [x] `renderer.h` - Rendering utilities
  - [x] `input.h` - Input handling
  - [x] `game_logic.h` - Game update logic
  - [x] `network.h` - Socket communication
- [x] Split code into modular source files
- [x] Add proper error handling
- [x] Add logging/debug output
- [x] Organize functions (render, update, input handling)
- [x] Add Doxygen-style documentation to all headers

## 🌐 Networking
- [x] Initialize Winsock2 for Windows
- [x] Create TCP socket connection
- [x] Implement connectToServer() with hostname resolution
- [x] Add non-blocking socket I/O
- [x] Implement sendToServer() function
- [x] Implement receiveFromServer() function
- [x] Add connection status tracking
- [x] Connect to Java server (localhost:2021)
- [ ] Implement message protocol (send/receive player commands)
- [ ] Handle server disconnection gracefully
- [ ] Add reconnection logic

## 📦 Build & Assets
- [x] Set up CMake build system
- [x] Configure SDL3 library linking (MinGW)
- [x] Link Winsock2 library for networking
- [x] Create VS Code build tasks
- [x] Configure nearest neighbor texture filtering
- [x] Add all source files to CMakeLists.txt
- [x] Organize asset directories:
  - [x] Add font file to `assets/font/`
  - [x] Add background graphic to `assets/img/`
  - [x] Add player spritesheet (dk-jr.bmp) to `assets/img/`
  - [ ] Add menu sounds to `assets/sound/`

---

## 📋 Current Sprint
**Completed:**
- ✅ SDL3 window initialization and rendering
- ✅ Basic main menu with navigation (3 options)
- ✅ Game state system (Menu/Playing/Quit)
- ✅ Background image loading and rendering
- ✅ Server-controlled player system with updatePlayerFromServer()
- ✅ Player sprite animations (IDLE, WALK, CLIMB)
- ✅ Enemy spawning and management system
- ✅ Code organization into 8 modular files
- ✅ TCP socket networking with Java server
- ✅ Hostname resolution (localhost support)
- ✅ Doxygen documentation for all APIs

**Priority Tasks:**
1. Implement server communication protocol (send input, receive game state)
2. Add text rendering for menu labels
3. Add platforms/level geometry
4. Implement jumping mechanics
5. Add player-enemy collision detection

**Notes:**
- SDL3 development package located at: `D:\Libraries\SDL3-3.2.26-mingw`
- Build system configured and working
- Focus on window and menu only for now