/*
** EPITECH PROJECT, 2024
** Assets.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <iostream>
#include <filesystem>

#include "Renderer/Camera.hpp"
#include "Renderer/DisplayTile.hpp"

namespace zappy
{
    class Assets
    {
        public:
            Assets();
            ~Assets();

            class AssetsError : public std::exception
            {
                public:
                    AssetsError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            sf::Font font;
            sf::Image placeholderImage;
            std::vector<std::unique_ptr<sf::Image>> tilesTextures;
            render3d::Camera camera;

            std::vector<std::shared_ptr<sf::Texture>> foodTextures;
            std::vector<std::shared_ptr<sf::Texture>> linemateTextures;
            std::vector<std::shared_ptr<sf::Texture>> deraumereTextures;
            std::vector<std::shared_ptr<sf::Texture>> siburTextures;
            std::vector<std::shared_ptr<sf::Texture>> mendianeTextures;
            std::vector<std::shared_ptr<sf::Texture>> phirasTextures;
            std::vector<std::shared_ptr<sf::Texture>> thystameTextures;

            sf::Texture eggTexture;
            sf::Texture towardsCameraTexture;
            sf::Texture towardsLeftTexture;
            sf::Texture towardsRightTexture;
            sf::Texture towardsBackTexture;
    };
}
