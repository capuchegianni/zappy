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

int main(int ac, char **av) {
    try {
        zappy::Communication server(4242, "localhost");
        server.connect();
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
