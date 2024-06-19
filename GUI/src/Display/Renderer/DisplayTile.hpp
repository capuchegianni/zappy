/*
** EPITECH PROJECT, 2024
** DisplayTile.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "Camera.hpp"
#include "../Assets.hpp"

#include "../../../include/Math/Ray3D.hpp"

namespace zappy
{
    namespace render3d
    {
        class DisplayTile
        {
            public:
                DisplayTile(sf::Image &tile);
                DisplayTile(const DisplayTile &other);
                ~DisplayTile();

                void computeTileImage(Camera &camera);
                sf::Texture &getTexture();

            private:
                sf::Image &_baseImage;
                sf::Texture _displayTexture;
                sf::Image _scaledImage;
        };
    }
}
