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
#include "Display/Renderer/Tile.hpp"

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    zappy::Assets assets;
    zappy::render3d::Camera camera;
    zappy::render3d::Tile tile(assets);

    window.setFramerateLimit(60);

    camera.rotate(math::Vector3D(0, 0, 0));

    tile.computeTileImage(camera);

    while (1) {
        window.clear();
        camera.rotate(math::Vector3D(0.1, 0.1, 0.1));
        tile.computeTileImage(camera);
        window.draw(tile);
        window.display();
    }
}
