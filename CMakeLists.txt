cmake_minimum_required(VERSION 3.0)
project(arjuno CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)
add_executable(arjuno src/main.cpp src/Game.cpp src/Game.h)
target_link_libraries(arjuno PRIVATE raylib)
target_compile_definitions(arjuno PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(arjuno PUBLIC SHADERS_PATH_330="${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl330/") # Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(arjuno PUBLIC SHADERS_PATH_100="${CMAKE_CURRENT_SOURCE_DIR}/shaders/glsl100/") # Set the asset path macro to the absolute path on the dev machine

#target_compile_definitions(arjuno PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release more
