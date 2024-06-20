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

    std::size_t width = 10;
    std::size_t height = 10;

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

    std::string team1 = "team1";
    std::string team2 = "team2";
    std::string team3 = "team3";
    std::string team4 = "team4";

    map.addTeam(team1);
    map.addTeam(team2);
    map.addTeam(team3);
    map.addTeam(team4);

    std::shared_ptr<zappy::Trantorien> player1 = std::make_shared<zappy::Trantorien>();

    player1->id = 1;
    player1->level = 1;
    player1->x = 0;
    player1->y = 0;

    map.addPlayer(player1, team1);

    std::shared_ptr<zappy::Trantorien> player2 = std::make_shared<zappy::Trantorien>();

    player2->id = 2;
    player2->level = 1;
    player2->x = 1;
    player2->y = 1;

    map.addPlayer(player2, team2);

    std::shared_ptr<zappy::Trantorien> player3 = std::make_shared<zappy::Trantorien>();

    player3->id = 3;
    player3->level = 1;
    player3->x = 2;
    player3->y = 2;

    map.addPlayer(player3, team3);

    std::shared_ptr<zappy::Trantorien> player4 = std::make_shared<zappy::Trantorien>();

    player4->id = 4;
    player4->level = 1;
    player4->x = 3;
    player4->y = 3;

    map.addPlayer(player4, team4);

    std::size_t frame = 0;

    srand(time(NULL));
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            map(i, j).thystame = rand() % 2;
            map(i, j).linemate = rand() % 2;
            map(i, j).food = rand() % 2;
            map(i, j).deraumere = rand() % 2;
            map(i, j).sibur = rand() % 2;
            map(i, j).mendiane = rand() % 2;
            map(i, j).phiras = rand() % 2;
        }
    }

    while (window.isOpen())
    {
        if (!(frameClock.getElapsedTime().asMilliseconds() > 1000 / 60)) {
            continue;
        }

        if (frame % 10 == 0)
        {
            zappy::Trantorien &player = *map.getPlayerById(1);
            player.x = (player.x + 1) % width;
            player.y = (player.y + 1) % height;

            zappy::Trantorien &player2 = *map.getPlayerById(2);
            player2.x = (player2.x - 1) % width;
            player2.y = (player2.y + 1) % height;
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
        frame++;
    }

    return 0;
}
