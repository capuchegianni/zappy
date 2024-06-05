/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** zappy_gui
*/

#include "Camera.hpp"

zappy::render3d::Camera::Camera() : size(0), aspectRatio(0), xOffset(0) {}

zappy::render3d::Camera::~Camera() = default;

zappy::Point3D zappy::render3d::Camera::projectPoint(Point3D point) const
{
    Vector3D v = point - Point3D(xOffset, yOffset, 0);
    double distance = v.dot(direction);
    Point3D projection = point - (direction * distance);

    return projection;
}
