cmake_minimum_required(VERSION 3.28)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -O0 -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(zappy_gui
        src/main.cpp)
