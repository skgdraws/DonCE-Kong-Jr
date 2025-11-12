cmake_minimum_required(VERSION 3.10)
project(DonCE-Kong-Jr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set SDL3 paths
set(SDL3_DIR "D:/Libraries/SDL3-3.2.26-mingw")
set(SDL3_INCLUDE_DIR "${SDL3_DIR}/x86_64-w64-mingw32/include")
set(SDL3_LIBRARY "${SDL3_DIR}/x86_64-w64-mingw32/lib/libSDL3.dll.a")

# Add executable
add_executable(main main.c)

# Include SDL3 headers
target_include_directories(main PRIVATE ${SDL3_INCLUDE_DIR})

# Link SDL3 library
target_link_libraries(main ${SDL3_LIBRARY})

# Copy SDL3.dll to build directory
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL3.dll
    $<TARGET_FILE_DIR:main>)

message(STATUS "Using SDL3 from: ${SDL3_DIR}")

# Set output directory to project root for convenience
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
