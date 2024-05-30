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

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Close);
    zappy::Map map(10, 10);

    window.setFramerateLimit(60);

    sf::Vector2f position(0, 0);
    sf::Vector2f size(1080, 1080);

    map.addPlayer(std::make_shared<zappy::Trantorien>(0));
    map.addPlayer(std::make_shared<zappy::Trantorien>(1));
    map.addPlayer(std::make_shared<zappy::Trantorien>(2));
    map.addPlayer(std::make_shared<zappy::Trantorien>(3));

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

    window.draw(map);
    window.display();

    while (1)
    {
        window.clear(sf::Color::Blue);
        window.draw(map);
        window.display();
    }
}
