cmake_minimum_required(VERSION 3.28)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g3 -O0 -fno-omit-frame-pointer")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(zappy_gui
        src/main.cpp
        src/Map/Map.hpp
        src/Map/Map.cpp
        src/Characters/Trantorien.hpp
        src/Characters/Trantorien.cpp
        src/Map/Box.hpp
        src/Map/Box.cpp
        src/Display/Assets.hpp
        src/Display/Assets.cpp
        src/Display/EventLogger.hpp
        src/Display/EventLogger.cpp
        src/Characters/Team.hpp
        src/Characters/Team.cpp
)

target_link_libraries(zappy_gui sfml-graphics sfml-window sfml-system)