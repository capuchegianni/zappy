/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>

#include "../../../include/Math/Ray3D.hpp"

namespace zappy
{
    namespace render3d
    {
        /**
         * @brief Orthographic camera class
         *
         */
        class Camera
        {
            public:
                Camera();
                ~Camera();

                size_t size;
                double aspectRatio;

                double scale;

                double xOffset;
                double yOffset;

                Vector3D direction;

                Point3D projectPoint(Point3D point) const;
        };
    }
}
