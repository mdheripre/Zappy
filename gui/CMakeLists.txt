cmake_minimum_required(VERSION 3.16)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

include_directories(
    src
    ${RAYLIB_INCLUDE_DIRS}
)

add_executable(zappy_gui ${SOURCES})

target_link_libraries(zappy_gui
    ${RAYLIB_LIBRARIES}
    m   # math
    pthread
    dl
    rt
    X11
)
