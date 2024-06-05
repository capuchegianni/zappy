/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** zappy_gui
*/

#include "Camera.hpp"

zappy::render3d::Camera::Camera() : size(0), aspectRatio(0), xOffset(0) {}

zappy::render3d::Camera::~Camera() = default;

math::Point3D zappy::render3d::Camera::projectPoint(math::Point3D point) const
{
    math::Vector3D v = point - math::Point3D(xOffset, yOffset, 0);
    double distance = v.dot(direction);
    math::Point3D projection = point - (direction * distance);

    return projection;
}

void zappy::render3d::Camera::rotate(math::Vector3D direction)
{
    math::Point3D center = math::Point3D(0, 0, 0);
    math::Point3D point = direction;

    math::Point3D newPoint = math::Point3D::rotateAroundCenter(center, point, direction.x, direction.y, direction.z);

    direction = math::Vector3D(newPoint.x, newPoint.y, newPoint.z);
}
