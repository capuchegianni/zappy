/*
** EPITECH PROJECT, 2024
** Assets.cpp
** File description:
** zappy_gui
*/

#include "Assets.hpp"

zappy::Assets::Assets()
{
    if (!font.loadFromFile("assets/fonts/LEMONMILK-Regular.otf"))
        throw Assets::AssetsError("Could not load font");

    if (!placeholderImage.loadFromFile("assets/textures/placeholder.png"))
        throw Assets::AssetsError("Could not load placeholder _baseImage");

    if (!compassTexture.loadFromFile("assets/textures/compass.png"))
        throw Assets::AssetsError("Could not load compass texture");

    if (!selectionTexture.loadFromFile("assets/textures/selection.png"))
        throw Assets::AssetsError("Could not load selection texture");

    // load all png and jpg files in assets/textures/tiles
    for (const auto &entry : std::filesystem::directory_iterator("assets/textures/tiles")) {
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
        if (!texture->loadFromFile("assets/textures/crystals/food/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load food " + std::to_string(i) + " texture");
        foodTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/linemate/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load linemate " + std::to_string(i) + " texture");
        linemateTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/deraumere/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load deraumere " + std::to_string(i) + " texture");
        deraumereTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/sibur/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load sibur " + std::to_string(i) + " texture");
        siburTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/mendiane/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load mendiane " + std::to_string(i) + " texture");
        mendianeTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/phiras/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load phiras " + std::to_string(i) + " texture");
        phirasTextures.push_back(texture);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/textures/crystals/thystame/" + std::to_string(i) + ".png"))
            throw Assets::AssetsError("Could not load thystame " + std::to_string(i) + " texture");
        thystameTextures.push_back(texture);
    }

    if (!eggTexture.loadFromFile("assets/textures/characters/egg.png"))
        throw Assets::AssetsError("Could not load egg texture");

    if (!towardsCameraTexture.loadFromFile("assets/textures/characters/towards_camera.png"))
        throw Assets::AssetsError("Could not load towards camera texture");

    if (!towardsLeftTexture.loadFromFile("assets/textures/characters/towards_left.png"))
        throw Assets::AssetsError("Could not load towards left texture");

    if (!towardsRightTexture.loadFromFile("assets/textures/characters/towards_right.png"))
        throw Assets::AssetsError("Could not load towards right texture");

    if (!towardsBackTexture.loadFromFile("assets/textures/characters/towards_back.png"))
        throw Assets::AssetsError("Could not load towards back texture");
}

zappy::Assets::~Assets() = default;
