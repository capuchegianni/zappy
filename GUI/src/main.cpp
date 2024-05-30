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
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    zappy::Map map;

    window.setFramerateLimit(60);

    sf::Vector2f position(50, 20);
    sf::Vector2f size(512, 512);

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
