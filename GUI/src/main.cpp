/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** GUI
*/

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"
#include "Display/Renderer/Camera.hpp"
#include "Display/Renderer/DisplayTile.hpp"

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    zappy::Assets assets;
    zappy::render3d::Camera camera;

    std::size_t width = 100;
    std::size_t height = 100;

    window.setFramerateLimit(60);

    camera.rotate(math::Vector3D(-45, 0, -45));
    camera.centerX = 0;
    camera.centerY = 0;
    camera.centerZ = 0.0;

    std::vector<std::unique_ptr<zappy::render3d::DisplayTile>> tiles;
    for (auto &tileTexture : assets.tilesTextures) {
        tiles.push_back(std::make_unique<zappy::render3d::DisplayTile>(*tileTexture));
    }

    std::vector<sf::Sprite> sprites;

    sf::Event event;
    sf::Clock frameClock;
    double lastFrameTime = 0;

    for (auto &tile : tiles) {
                tile->computeTileImage(camera);
    }

    sprites.clear();

    for (std::size_t i = 0; i < width; i++) {
        for (std::size_t j = 0; j < height; j++) {
            sf::Sprite sprite;
            int random_index = rand() % assets.tilesTextures.size();

            sprite.setTexture(tiles[random_index]->getTexture());
            sprite.setOrigin(tiles[random_index]->getTexture().getSize().x / 2, tiles[random_index]->getTexture().getSize().y / 2);
            sprites.push_back(sprite);
        }
    }

    while (window.isOpen()) {
        if (!(frameClock.getElapsedTime().asMilliseconds() > 1000 / 60)) {
            continue;
        }

        bool didRotate = false;
        math::Vector3D movForward = camera.direction * 0.01 * lastFrameTime;
        math::Vector3D movRight = camera.right * 0.01 * lastFrameTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            camera.centerX += movForward.x * lastFrameTime * 0.1;
            camera.centerY += movForward.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            camera.centerX -= movForward.x * lastFrameTime * 0.1;
            camera.centerY -= movForward.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            camera.centerX += movRight.x * lastFrameTime * 0.1;
            camera.centerY += movRight.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            camera.centerX -= movRight.x * lastFrameTime * 0.1;
            camera.centerY -= movRight.y * lastFrameTime * 0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && camera.unitaryPixelsSize < 200)
        {
            camera.unitaryPixelsSize += 1;
            camera.rotate(math::Vector3D(0, 0, 0));
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && camera.unitaryPixelsSize > 10)
        {
            camera.unitaryPixelsSize -= 1;
            camera.rotate(math::Vector3D(0, 0, 0));
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.rotate(math::Vector3D(0, 0, 1 * lastFrameTime) * 0.1);
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.rotate(math::Vector3D(0, 0, -1 * lastFrameTime * 0.1));
            didRotate = true;
        }

        if (didRotate)
        {
            for (auto &tile : tiles) {
                tile->computeTileImage(camera);
            }

            sprites.clear();

            for (std::size_t i = 0; i < width; i++) {
                for (std::size_t j = 0; j < height; j++) {
                    sf::Sprite sprite;
                    int random_index = rand() % assets.tilesTextures.size();

                    sprite.setTexture(tiles[random_index]->getTexture());
                    sprite.setOrigin(tiles[random_index]->getTexture().getSize().x / 2, tiles[random_index]->getTexture().getSize().y / 2);
                    sprites.push_back(sprite);
                }
            }
        }

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        for (std::size_t i = 0; i < width; i++) {
            for (std::size_t j = 0; j < height; j++) {
                sf::Sprite &sprite = sprites[i * width + j];
                sprite.setPosition(camera.displayUnitaryX.x * i + camera.displayUnitaryY.x * j + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ + window.getSize().x / 2,
                                   camera.displayUnitaryX.y * i + camera.displayUnitaryY.y * j + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ + window.getSize().y / 2);
            }
        }

        window.clear();
        for (auto &sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
        lastFrameTime = frameClock.getElapsedTime().asMilliseconds();
        frameClock.restart();
    }

    return 0;
}
