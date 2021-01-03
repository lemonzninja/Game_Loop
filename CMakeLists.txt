cmake_minimum_required(VERSION 3.17)
project(Game_Loop C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

add_executable(Game.appimage main.c)

target_link_libraries(Game.appimage ${SDL2_LIBRARIES})