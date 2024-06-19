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
#include <SFML/Graphics/RenderTexture.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"
#include "Display/Renderer/Camera.hpp"
#include "Display/Renderer/DisplayTile.hpp"

int main(int ac, char **av)
{
    int winwidth = 1920;
    int winheight = 1080;

    sf::RenderWindow window(sf::VideoMode(winwidth, winheight), "Zappy");
    zappy::Assets assets;

    std::size_t width = 30;
    std::size_t height = 30;

    window.setFramerateLimit(60);

    zappy::Map map(width, height, assets);

    sf::Event event;
    sf::Clock frameClock;
    int lastFrameTime = 0;

    frameClock.restart();

    sf::View view(sf::FloatRect(-(static_cast<float>(winwidth) / 2) + 250, -(static_cast<float>(winheight) / 2) + 250, static_cast<float>(winwidth), static_cast<float>(winheight)));

    sf::Vector2f rawr = {-300, -300};
    sf::Vector2f rawr2 = {600, 600};
    map.setDisplayPosition(rawr);
    map.setDisplaySize(rawr2);

    while (window.isOpen()) {
        if (!(frameClock.getElapsedTime().asMilliseconds() > 1000 / 60)) {
            continue;
        }

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
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map.sceneDate.sceneData.camera.unitaryPixelsSize > 10)
        {
            map.sceneDate.sceneData.camera.unitaryPixelsSize -= 1;
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, 1 * lastFrameTime) * 0.1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            map.sceneDate.sceneData.camera.rotate(math::Vector3D(0, 0, -1 * lastFrameTime * 0.1));
        }

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                view = sf::View(sf::FloatRect(-(static_cast<float>(event.size.width) / 2), -(static_cast<float>(event.size.height) / 2), static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
                window.setView(view);
            }
        }

        map.updateDisplay();
        window.clear(sf::Color::Blue);
        window.draw(map);
        window.display();
        lastFrameTime = frameClock.getElapsedTime().asMilliseconds();
        frameClock.restart();
    }

    return 0;
}
