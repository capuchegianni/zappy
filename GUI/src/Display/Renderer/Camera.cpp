/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** zappy_gui
*/

#include "Camera.hpp"

zappy::render3d::Camera::Camera() : size(0), aspectRatio(0), xOffset(0), direction(0, 0, 1), up(0, 1, 0), right(1, 0, 0) {}

zappy::render3d::Camera::~Camera() = default;

math::Point3D zappy::render3d::Camera::projectPoint(math::Point3D point) const
{
    // Epsilon value for floating point comparisons
    double epsilon = 0.0001;

    // Plane's origin point
    math::Point3D planePoint(0, 0, 0);

    // Vector from the plane point to the target point
    math::Vector3D v = point - planePoint;

    // Distance from the point to the plane along the direction
    double distance = v.dot(direction);

    // Projection of the point onto the plane
    math::Point3D projection = point - (direction * distance);

    // Use the camera's up and right vectors to create the plane's basis vectors
    math::Vector3D x = right;
    math::Vector3D y = up;

    // Project the 3D projection point onto the 2D plane basis vectors
    double ux = math::Vector3D(projection.x, projection.y, projection.z).dot(x);
    double vx = math::Vector3D(projection.x, projection.y, projection.z).dot(y);

    // Return the 2D coordinates
    return math::Point3D(ux, vx, 0);
}


void zappy::render3d::Camera::rotate(math::Vector3D rotation)
{
    math::Point3D center(0, 0, 0);

    math::Point3D newDirection = direction;
    newDirection = math::Point3D::rotateAroundCenter(newDirection, center, rotation.x, rotation.y, rotation.z);
    direction = math::Vector3D(newDirection.x, newDirection.y, newDirection.z);
    direction.normalize();

    math::Point3D newUp = up;
    newUp = math::Point3D::rotateAroundCenter(newUp, center, rotation.x, rotation.y, rotation.z);
    up = math::Vector3D(newUp.x, newUp.y, newUp.z);
    up.normalize();

    math::Point3D newRight = right;
    newRight = math::Point3D::rotateAroundCenter(newRight, center, rotation.x, rotation.y, rotation.z);
    right = math::Vector3D(newRight.x, newRight.y, newRight.z);
    right.normalize();
}
