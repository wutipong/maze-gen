cmake_minimum_required(VERSION 3.21)
set(
    CMAKE_TOOLCHAIN_FILE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING 
    "Vcpkg toolchain file"
)

set(CMAKE_CXX_STANDARD 20)

# set the project name
project(maze-gen)

add_library(
    maze-gen 
    src/maze.cpp
    src/maze_context.cpp
    src/maze_path.cpp
)

target_include_directories(maze-gen PUBLIC include)

# Tests
find_package(Catch2 CONFIG REQUIRED)

add_executable(
    tests 
    test/main.cpp 
    test/maze.cpp
    test/maze_context.cpp
    test/maze_path.cpp
    test/maze_path_benchmark.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2 maze-gen)
target_include_directories(tests PRIVATE Catch2::Catch2)