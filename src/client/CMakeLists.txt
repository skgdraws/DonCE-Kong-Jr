cmake_minimum_required(VERSION 3.10)
project(DonCE-Kong-Jr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set SDL3 paths
set(SDL3_DIR "D:/Libraries/SDL3-3.2.26-mingw")
set(SDL3_INCLUDE_DIR "${SDL3_DIR}/x86_64-w64-mingw32/include")
set(SDL3_LIBRARY "${SDL3_DIR}/x86_64-w64-mingw32/lib/libSDL3.dll.a")

# Set SDL3_ttf paths
set(SDL3_TTF_DIR "D:/Libraries/SDL3_ttf-3.2.2")
set(SDL3_TTF_INCLUDE_DIR "${SDL3_TTF_DIR}/x86_64-w64-mingw32/include")
set(SDL3_TTF_LIBRARY "${SDL3_TTF_DIR}/x86_64-w64-mingw32/lib/libSDL3_ttf.dll.a")
set(SDL3_TTF_DLL "${SDL3_TTF_DIR}/x86_64-w64-mingw32/bin/SDL3_ttf.dll")

# Add executable
add_executable(main 
    src/main.c
    src/game_state.c
    src/player.c
    src/enemy.c
    src/assets.c
    src/renderer.c
    src/input.c
    src/game_logic.c
    src/network.c
)

# Include SDL3 headers
target_include_directories(main PRIVATE ${SDL3_INCLUDE_DIR} ${SDL3_TTF_INCLUDE_DIR})

# Link SDL3 library
target_link_libraries(main ${SDL3_LIBRARY} ${SDL3_TTF_LIBRARY})

# Link Winsock2 for Windows networking
if(WIN32)
    target_link_libraries(main ws2_32)
endif()

# Copy SDL3.dll to project root directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SDL3_DIR}/x86_64-w64-mingw32/bin/SDL3.dll
    ${CMAKE_CURRENT_SOURCE_DIR})

# Copy SDL3_ttf.dll to project root directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SDL3_TTF_DLL}
    ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Using SDL3 from: ${SDL3_DIR}")

# Set output directory to project root for convenience
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
