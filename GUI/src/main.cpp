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

    camera.rotate(math::Vector3D(0, 0, 0));

    tile.computeTileImage(camera);

    sf::Sprite sprite(tile.getTexture());

    while (1) {
        window.clear();
        camera.rotate(math::Vector3D(5, 5, 5));
        tile.computeTileImage(camera);
        sprite = sf::Sprite(tile.getTexture());
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
        sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        window.draw(sprite);
        window.display();
    }
}
