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
    int winwidth = 1920;
    int winheight = 1080;

    sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Zappy", sf::Style::Close);
    zappy::Assets assets;

    std::size_t width = 10;
    std::size_t height = 10;

    window.setFramerateLimit(60);

    zappy::Map map(width, height, assets);

    sf::Event event;
    sf::Clock frameClock;
    int lastFrameTime = 0;

    frameClock.restart();

    sf::View view(sf::FloatRect(-winwidth/2, -winheight/2, winwidth, winheight));
    window.setView(view);

    while (window.isOpen()) {
        if (!(frameClock.getElapsedTime().asMilliseconds() > 1000 / 60)) {
            continue;
        }

        bool didRotate = false;
        math::Vector3D movForward = map.sceneDate.sceneData.camera.direction * 0.01 * lastFrameTime;
        math::Vector3D movRight = map.sceneDate.sceneData.camera.right * 0.01 * lastFrameTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            map.sceneDate.sceneData.camera.centerX += movForward.x * lastFrameTime * 0.1;
            map.sceneDate.sceneData.camera.centerY += movForward.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            map.sceneDate.sceneData.camera.centerX -= movForward.x * lastFrameTime * 0.1;
            map.sceneDate.sceneData.camera.centerY -= movForward.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            map.sceneDate.sceneData.camera.centerX += movRight.x * lastFrameTime * 0.1;
            map.sceneDate.sceneData.camera.centerY += movRight.y * lastFrameTime * 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            map.sceneDate.sceneData.camera.centerX -= movRight.x * lastFrameTime * 0.1;
            map.sceneDate.sceneData.camera.centerY -= movRight.y * lastFrameTime * 0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map.sceneDate.sceneData.camera.unitaryPixelsSize < 200)
        {
            map.sceneDate.sceneData.camera.unitaryPixelsSize += 1;
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 0));
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map.sceneDate.sceneData.camera.unitaryPixelsSize > 10)
        {
            map.sceneDate.sceneData.camera.unitaryPixelsSize -= 1;
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 0));
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 1 * lastFrameTime) * 0.1);
            didRotate = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, -1 * lastFrameTime * 0.1));
            didRotate = true;
        }

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        map.updateDisplay();
        window.clear();

        window.draw(map);
        window.display();
        lastFrameTime = frameClock.getElapsedTime().asMilliseconds();
        frameClock.restart();
    }

    return 0;
}
