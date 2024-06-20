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

    // load all png and jpg files in assets/textures/tiles
    for (const auto &entry : std::filesystem::directory_iterator("../assets/textures/tiles")) {
        if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
        {
            sf::Image texture;
            if (!texture.loadFromFile(entry.path().string()))
                throw Assets::AssetsError("Could not load tile texture");
            tilesTextures.push_back(std::make_unique<sf::Image>(texture));
        }
    }

    for (int i = 0; i < 5; i++)
    {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/food" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load food " + std::to_string(i) + " texture");
        foodTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/linemate" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load linemate " + std::to_string(i) + " texture");
        linemateTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/deraumere" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load deraumere " + std::to_string(i) + " texture");
        deraumereTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/sibur" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load sibur " + std::to_string(i) + " texture");
        siburTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/mendiane" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load mendiane " + std::to_string(i) + " texture");
        mendianeTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/phiras" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load phiras " + std::to_string(i) + " texture");
        phirasTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("../assets/textures/thystame" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load thystame " + std::to_string(i) + " texture");
        thystameTextures.push_back(texture);
    }
}

zappy::Assets::~Assets() = default;
