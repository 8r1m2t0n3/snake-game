cmake_minimum_required(VERSION 3.5)

project(snake_game)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    main.cpp
    src/coordinates.cpp
    src/direction.cpp
    src/console_handler.cpp
    src/window.cpp
    src/snake.cpp
    src/game.cpp
)

add_executable(snake_game ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)