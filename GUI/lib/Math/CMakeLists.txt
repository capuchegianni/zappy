cmake_minimum_required(VERSION 3.27)
project(Math)

set(CMAKE_CXX_STANDARD 17)

add_library(Math STATIC
        src/Matrix.hpp
        src/Matrix.cpp
        src/Point3D.hpp
        src/Point3D.cpp
        src/Ray3D.hpp
        src/Ray3D.cpp
        src/Rectangle3D.hpp
        src/Rectangle3D.cpp
        src/Vector3D.hpp
        src/Vector3D.cpp)
