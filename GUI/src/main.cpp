/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** GUI
*/

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"
#include "Display/Renderer/Camera.hpp"
#include "Display/Renderer/DisplayTile.hpp"

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    zappy::Assets assets;
    zappy::render3d::Camera camera;
    zappy::render3d::DisplayTile tile(assets);

    window.setFramerateLimit(60);

    camera.rotate(math::Vector3D(45, 0, 45));

    tile.computeTileImage(camera);

    std::vector<sf::Sprite> sprites;

    for (int i = -5; i < 5; i++) {
        for (int j = -5; j < 5; j++) {
            sf::Sprite sprite;
            sprite.setTexture(tile.getTexture());
            sprite.setOrigin(tile.getTexture().getSize().x / 2, tile.getTexture().getSize().y / 2);
            sprite.setPosition(camera.displayUnitaryX.x * i + camera.displayUnitaryY.x * j + camera.displayUnitaryZ.x * i + window.getSize().x / 2,
                               camera.displayUnitaryX.y * i + camera.displayUnitaryY.y * j + camera.displayUnitaryZ.y * i + window.getSize().y / 2);
            sprites.push_back(sprite);
        }
    }

    bool rsising = false;

    while (1) {
        camera.rotate(math::Vector3D(0, 0, 1));
        tile.computeTileImage(camera);
        sprites.clear();

        if (rsising)
        {
            camera.unitaryPixelsSize++;
            if (camera.unitaryPixelsSize > 100)
                rsising = false;
        }

        else
        {
            camera.unitaryPixelsSize--;
            if (camera.unitaryPixelsSize < 4)
                rsising = true;
        }

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                sf::Sprite sprite;
                sprite.setTexture(tile.getTexture());
                sprite.setOrigin(tile.getTexture().getSize().x / 2, tile.getTexture().getSize().y / 2);
                sprite.setPosition(camera.displayUnitaryX.x * i + camera.displayUnitaryY.x * j + window.getSize().x / 2,
                                   camera.displayUnitaryX.y * i + camera.displayUnitaryY.y * j + window.getSize().y / 2);
                sprites.push_back(sprite);
            }
        }
        window.clear();
        for (auto &sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
    }
}
