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

    sf::Vector2f position(0, 0);
    sf::Vector2f size(250, 250);

    map.setMapDisplayPosition(position);
    map.setMapDisplaySize(size);

    window.draw(map);
    window.display();

    while (1);
}
