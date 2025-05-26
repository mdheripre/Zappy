cmake_minimum_required(VERSION 3.16)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
)

include_directories(include)
add_executable(zappy_gui ${SOURCES})