/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** GUI
*/

#include <iostream>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"
#include "Communication/Communication.hpp"

int main(int ac, char **av)
{
    try {
        zappy::Communication server(5001, "10.17.70.247");
        server.connect();
        server.run();
    } catch (std::exception &e) {
        try {
            zappy::Communication server(5000, "10.17.70.247");
            server.connect();
            server.run();
        } catch (std::exception &e) {
            try {
                zappy::Communication server(4242, "localhost");
                server.connect();
                server.run();
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    }
    /*

    std::string team1 = "Team 1";
    std::string team2 = "Team 2";
    std::string team3 = "Team 3";
    std::string team4 = "Team 4";

    map.addTeam(team1);
    map.addTeam(team2);
    map.addTeam(team3);
    map.addTeam(team4);

    map.addPlayer(std::make_shared<zappy::Trantorien>(0), team1);
    map.addPlayer(std::make_shared<zappy::Trantorien>(1), team2);
    map.addPlayer(std::make_shared<zappy::Trantorien>(2), team3);
    map.addPlayer(std::make_shared<zappy::Trantorien>(3), team4);

    map.getPlayerById(0)->x = 2;
    map.getPlayerById(0)->y = 2;
    map.getPlayerById(0)->direction = zappy::Direction::UP;

    map.getPlayerById(1)->x = 3;
    map.getPlayerById(1)->y = 3;
    map.getPlayerById(1)->direction = zappy::Direction::LEFT;

    map.getPlayerById(2)->x = 4;
    map.getPlayerById(2)->y = 4;
    map.getPlayerById(2)->direction = zappy::Direction::DOWN;

    map.getPlayerById(3)->x = 5;
    map.getPlayerById(3)->y = 5;
    map.getPlayerById(3)->direction = zappy::Direction::RIGHT;

    map.setDisplayPosition(position);
    map.setDisplaySize(size);

    map(0, 0).food = 1;
    map(0, 0).linemate = 1;
    map(0, 0).deraumere = 1;
    map(0, 0).sibur = 1;
    map(0, 0).mendiane = 1;
    map(0, 0).phiras = 1;
    map(0, 0).thystame = 1;

    for (std::size_t y = 0; y < height; y++)
    {
        for (std::size_t x = 0; x < width; x++)
        {
            map(x, y).food = rand() % 10;
            map(x, y).linemate = rand() % 10;
            map(x, y).deraumere = rand() % 10;
            map(x, y).sibur = rand() % 10;
            map(x, y).mendiane = rand() % 10;
            map(x, y).phiras = rand() % 10;
            map(x, y).thystame = rand() % 10;
        }
    }

    std::size_t frame = 0;

    std::string log = "Frame: " + std::to_string(frame);

    while (1)
    {
        log = "Frame: " + std::to_string(frame);

        window.clear(sf::Color::Blue);

        map(map.getPlayerById(0)->x, map.getPlayerById(0)->y).food++;
        map.getPlayerById(0)->x = (map.getPlayerById(0)->x + 1) % width;

        map(map.getPlayerById(1)->x, map.getPlayerById(1)->y).linemate++;
        map.getPlayerById(1)->x = (map.getPlayerById(1)->x + 1) % width;
        map.getPlayerById(1)->y = (map.getPlayerById(1)->y + 1) % height;

        map(map.getPlayerById(2)->x, map.getPlayerById(2)->y).deraumere++;
        map.getPlayerById(2)->x = (map.getPlayerById(2)->x - 1) % width;
        map.getPlayerById(2)->y = (map.getPlayerById(2)->y + 1) % height;

        map(map.getPlayerById(3)->x, map.getPlayerById(3)->y).sibur++;
        map.getPlayerById(3)->x = (map.getPlayerById(3)->x + 1) % width;
        map.getPlayerById(3)->y = (map.getPlayerById(3)->y - 1) % height;

        map.updateDisplay();

        eventLogger.log(log);

        window.draw(map);
        window.draw(eventLogger);
        window.display();

        frame++;
    }
}
