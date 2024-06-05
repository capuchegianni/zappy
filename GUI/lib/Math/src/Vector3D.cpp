/*
** EPITECH PROJECT, 2024
** Vector3D.cpp
** File description:
** math
*/

#include "Vector3D.hpp"

math::Vector3D math::Vector3D::operator+(const math::Vector3D &other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

math::Vector3D &math::Vector3D::operator+=(const math::Vector3D &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator-(const math::Vector3D &other) const
{
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

math::Vector3D &math::Vector3D::operator-=(const math::Vector3D &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator*(const math::Vector3D &other) const
{
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

math::Vector3D &math::Vector3D::operator*=(const math::Vector3D &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator/(const math::Vector3D &other) const
{
    return Vector3D(x / other.x, y / other.y, z / other.z);
}

math::Vector3D &math::Vector3D::operator/=(const math::Vector3D &other)
{
    x /= other.x; y /= other.y; z /= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator*(double scalar) const
{
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

math::Vector3D &math::Vector3D::operator*=(double scalar)
{
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
}

math::Vector3D math::Vector3D::operator/(double scalar) const
{
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

math::Vector3D &math::Vector3D::operator/=(double scalar)
{
    x /= scalar; y /= scalar; z /= scalar;
    return *this;
}

double math::Vector3D::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

double math::Vector3D::dot(const math::Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

math::Vector3D math::Vector3D::cross(const math::Vector3D &other) const
{
    return Vector3D(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
}

math::Vector3D math::Vector3D::normalize()
{
    double len = length();
    if (len == 0)
        return *this;

    return Vector3D(x / len, y / len, z / len);
}
