/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>

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

                double zAngle;
                double xAngle;
                double yAngle;
        };
    }
}
