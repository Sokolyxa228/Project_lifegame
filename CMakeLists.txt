cmake_minimum_required(VERSION 3.27)
project(Project_lifegame)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_lifegame
        Grass.cpp
        Grass.h
        main.cpp
        Obj.cpp
        Obj.h
        Sheep.h
        Sheep.cpp
        Wolfs.h
        Wolfs.cpp)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)



target_link_libraries(Project_lifegame sfml-graphics)

