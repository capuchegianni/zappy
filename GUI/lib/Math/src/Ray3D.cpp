/*
** EPITECH PROJECT, 2024
** Ray3D.cpp
** File description:
** math
*/

#include "Ray3D.hpp"

math::Ray3D::Ray3D() = default;
math::Ray3D::Ray3D(const math::Point3D &origin, const math::Vector3D &direction) : origin(origin), direction(direction) {}

math::Ray3D::~Ray3D() = default;

std::ostream &math::operator<<(std::ostream &os, const math::Ray3D &r)
{
    os << "Ray3D(" << r.origin << ", " << r.direction << ")"; return os;
}

math::Ray3D &math::Ray3D::operator=(const math::Ray3D &other){
    if (this == &other) { return *this; }
    origin = other.origin;
    direction = other.direction;

    return *this;
}
