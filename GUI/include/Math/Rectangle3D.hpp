/*
** EPITECH PROJECT, 2024
** Rectangle3D.hpp
** File description:
** raytracer
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace math
{
    class Rectangle3D
    {
        public:
            Rectangle3D(Point3D origin, Vector3D bottom_side, Vector3D left_side) : origin(origin), bottom_side(bottom_side), left_side(left_side) {};
            ~Rectangle3D();

            Point3D pointAt(double u, double v) const;
            void move(Vector3D direction);
            void rotate(Vector3D direction);

            Point3D origin;
            Vector3D bottom_side;
            Vector3D left_side;
    };
}
