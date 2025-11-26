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
- [x] Create player block/entity
- [x] Implement basic movement (WASD/Arrow keys)
- [x] Add collision with screen boundaries
- [x] Separate game logic into update function
- [ ] Add sprite/texture for player character
- [ ] Implement jumping mechanics
- [ ] Add platforms/level geometry
- [ ] Implement enemy entities

## 🔊 Audio for Menu
- [ ] Initialize SDL audio system
- [ ] Load menu background music (from `assets/sound/`)
- [ ] Load button hover/click sound effects
- [ ] Implement audio playback controls
- [ ] Add volume control (music and SFX)

## 🔧 Code Structure
- [ ] Create header files:
  - [ ] `window.h` - Window management
  - [ ] `menu.h` - Menu system
  - [ ] `renderer.h` - Rendering utilities
  - [ ] `audio.h` - Audio system
  - [ ] `player.h` - Player logic
  - [ ] `game.h` - Game state management
- [ ] Split code into multiple source files
- [x] Add proper error handling
- [x] Add logging/debug output
- [x] Organize functions (render, update, input handling)

## 📦 Build & Assets
- [x] Set up CMake build system
- [x] Configure SDL3 library linking (MinGW)
- [x] Create VS Code build tasks
- [x] Configure nearest neighbor texture filtering
- [x] Organize asset directories:
  - [ ] Add placeholder font file to `assets/font/`
  - [x] Add background graphic to `assets/img/`
  - [ ] Add menu sounds to `assets/sound/`

---

## 📋 Current Sprint
**Completed:**
- ✅ SDL3 window initialization and rendering
- ✅ Basic main menu with navigation (3 options)
- ✅ Game state system (Menu/Playing/Quit)
- ✅ Background image loading and rendering
- ✅ Player movement with keyboard controls
- ✅ Code organization (separate render/update/input functions)

**Priority Tasks:**
1. Add text rendering for menu labels
2. Implement player sprite/texture
3. Add basic level geometry (platforms)
4. Implement jumping mechanics

**Notes:**
- SDL3 development package located at: `D:\Libraries\SDL3-3.2.26-mingw`
- Build system configured and working
- Focus on window and menu only for now