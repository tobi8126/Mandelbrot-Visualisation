cmake_minimum_required(VERSION 4.2)
project(mandelbrot_visualisation C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG        6.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

add_executable(mandelbrot_visualisation main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)