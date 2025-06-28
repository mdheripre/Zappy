cmake_minimum_required(VERSION 3.16)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Recherche de SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

include_directories(
    src
    ${SFML_INCLUDE_DIR}
)

add_executable(zappy_gui ${SOURCES})

target_link_libraries(zappy_gui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

