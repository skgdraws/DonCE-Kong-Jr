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
- [ ] Handle window resize events
- [ ] Implement proper SDL cleanup on exit

## 🎮 Main Game Loop
- [ ] Create main event loop
- [ ] Implement frame rate limiting (target FPS)
- [ ] Add delta time calculation
- [ ] Handle quit events (window close, ESC key)
- [ ] Set up game state system (menu, playing, etc.)

## 📝 Main Menu UI
- [ ] Design main menu layout
- [ ] Load and render menu background
- [ ] Load font for menu text (from `assets/font/`)
- [ ] Create menu buttons:
  - [ ] Start Game
  - [ ] Spectate Game
  - [ ] Options/Settings
  - [ ] Exit
- [ ] Implement button hover effects
- [ ] Add button click detection
- [ ] Implement keyboard navigation (arrow keys, Enter)
- [ ] Add menu selection sound effects

## 🎨 Graphics & Rendering
- [ ] Load menu background image (from `assets/img/`)
- [ ] Implement texture loading system
- [ ] Create text rendering function
- [ ] Add menu logo/title graphic
- [ ] Implement basic color schemes

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
- [ ] Split code into multiple source files
- [ ] Add proper error handling
- [ ] Add logging/debug output

## 📦 Build & Assets
- [x] Set up CMake build system
- [x] Configure SDL3 library linking
- [x] Create VS Code build tasks
- [ ] Organize asset directories:
  - [ ] Add placeholder font file to `assets/font/`
  - [ ] Add menu graphics to `assets/img/`
  - [ ] Add menu sounds to `assets/sound/`

---

## 📋 Current Sprint
**Priority Tasks:**
1. Get SDL3 window displaying
2. Implement basic main menu with text
3. Add button interaction

**Notes:**
- SDL3 development package located at: `D:\Libraries\SDL3-3.2.26-mingw`
- Build system configured and working
- Focus on window and menu only for now