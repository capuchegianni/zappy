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
    zappy::render3d::DisplayTile tile(assets.placeholderImage);

    window.setFramerateLimit(60);

    camera.rotate(math::Vector3D(-45, 0, -45));
    camera.centerX = -2.0;
    camera.centerY = -2.0;
    camera.centerZ = 0.0;

    tile.computeTileImage(camera);

    std::vector<sf::Sprite> sprites;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            sf::Sprite sprite;
            sprite.setTexture(tile.getTexture());
            sprite.setOrigin(tile.getTexture().getSize().x / 2, tile.getTexture().getSize().y / 2);
            sprite.setPosition(camera.displayUnitaryX.x * i + camera.displayUnitaryY.x * j + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ + window.getSize().x / 2,
                                 camera.displayUnitaryX.y * i + camera.displayUnitaryY.y * j + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ + window.getSize().y / 2);
            sprites.push_back(sprite);
        }
    }

    sf::Event event;
    sf::Clock frameClock;

    while (window.isOpen()) {
        if (!(frameClock.getElapsedTime().asMilliseconds() > 1000 / 60)) {
            continue;
        }

        while (window.pollEvent(event)) {
            bool didRotate = false;

            if (event.type == sf::Event::Closed)
                window.close();

            math::Vector3D movForward = camera.direction * 0.01 * frameClock.getElapsedTime().asMilliseconds();
            math::Vector3D movRight = camera.right * 0.01 * frameClock.getElapsedTime().asMilliseconds();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                camera.centerX += movForward.x;
                camera.centerY += movForward.y;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                camera.centerX -= movForward.x;
                camera.centerY -= movForward.y;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                camera.centerX += movRight.x;
                camera.centerY += movRight.y;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                camera.centerX -= movRight.x;
                camera.centerY -= movRight.y;
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
                camera.rotate(math::Vector3D(0, 0, 1));
                didRotate = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                camera.rotate(math::Vector3D(0, 0, -1));
                didRotate = true;
            }

            if (didRotate)
            {
                tile.computeTileImage(camera);
                sprites.clear();

                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        sf::Sprite sprite;
                        sprite.setTexture(tile.getTexture());
                        sprite.setOrigin(tile.getTexture().getSize().x / 2, tile.getTexture().getSize().y / 2);
                        sprites.push_back(sprite);
                    }
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                sf::Sprite &sprite = sprites[i * 5 + j];
                sprite.setPosition(camera.displayUnitaryX.x * i + camera.displayUnitaryY.x * j + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ + window.getSize().x / 2,
                                   camera.displayUnitaryX.y * i + camera.displayUnitaryY.y * j + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ + window.getSize().y / 2);
            }

        }

        window.clear();
        for (auto &sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
        frameClock.restart();
    }

    return 0;
}
