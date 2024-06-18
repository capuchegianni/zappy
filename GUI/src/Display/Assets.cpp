/*
** EPITECH PROJECT, 2024
** Assets.cpp
** File description:
** zappy_gui
*/

#include "Assets.hpp"

zappy::Assets::Assets()
{
    if (!font.loadFromFile("../assets/fonts/LEMONMILK-Regular.otf"))
        throw Assets::AssetsError("Could not load font");

    if (!placeholderImage.loadFromFile("../assets/textures/placeholder.png"))
        throw Assets::AssetsError("Could not load placeholder _baseImage");

    // load all png files in assets/textures/tiles
    for (const auto &entry : std::filesystem::directory_iterator("../assets/textures/tiles")) {
        if (entry.path().extension() == ".png") {
            sf::Image texture;
            if (!texture.loadFromFile(entry.path().string()))
                throw Assets::AssetsError("Could not load tile texture");
            tilesTextures.push_back(std::make_unique<sf::Image>(texture));
        }
    }
}

zappy::Assets::~Assets() = default;
