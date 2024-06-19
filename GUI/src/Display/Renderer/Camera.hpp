/*
** EPITECH PROJECT, 2024
** Camera.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>
#include <SFML/System/Vector2.hpp>

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

                double centerX;
                double centerY;
                double centerZ;

                sf::Vector2f displayUnitaryX;
                sf::Vector2f displayUnitaryY;
                sf::Vector2f displayUnitaryZ;
                std::size_t unitaryPixelsSize;
                std::size_t unitaryPixelsSizeBackup;

                math::Vector3D direction;
                math::Vector3D up;
                math::Vector3D right;
                math::Vector3D directionBackup;

                math::Point3D projectPoint(math::Point3D point) const;
                void rotate(math::Vector3D direction);
        };
    }
}
