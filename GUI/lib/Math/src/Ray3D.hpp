/*
** EPITECH PROJECT, 2024
** Ray3D.hpp
** File description:
** raytracer
*/

#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace math
{
    class Ray3D
    {
        public:
            Ray3D();
            Ray3D(const Point3D &origin, const Vector3D &direction);
            ~Ray3D();

            Ray3D& operator=(const Ray3D& other);

            Point3D origin;

            Vector3D direction;

    };

    std::ostream &operator<<(std::ostream& os, const Ray3D& r);
}
