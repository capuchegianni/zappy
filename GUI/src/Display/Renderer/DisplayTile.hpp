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

                class DisplayTileError : public std::exception
                {
                    public:
                        DisplayTileError(std::string const &message) : _message(message) {}
                        const char *what() const noexcept override { return _message.c_str(); }
                    private:
                        std::string _message;
                };

                void computeTileImage(Camera &camera);
                void resizeImage(Camera &camera);
                void projectTile(Camera &camera);
                sf::Texture &getTexture();

            private:
                sf::Image &_baseImage;
                sf::Texture _displayTexture;
                sf::Image _scaledImage;
        };
    }
}
