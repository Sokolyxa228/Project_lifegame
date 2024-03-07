cmake_minimum_required(VERSION 3.27)
project(Project_lifegame)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_lifegame
        Grass.cpp
        Grass.h
        main.cpp
        Obj.cpp
        Obj.h
        Sheep.h)
set(SFML_INCLUDE_DIR "/usr/local/include")
set(SFML_LIBRARY_DIR "/usr/local/lib")
link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    target_link_libraries(Project_lifegame sfml-graphics sfml-window sfml-system)
endif()