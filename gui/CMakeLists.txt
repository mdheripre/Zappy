cmake_minimum_required(VERSION 3.16)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

include_directories(src)

add_executable(zappy_gui ${SOURCES})
