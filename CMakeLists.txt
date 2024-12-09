

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(emulator.app)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory (src)
add_subdirectory (lib)

target_include_directories (${PROJECT_NAME} PUBLIC
    .
    src/
    lib/
)

