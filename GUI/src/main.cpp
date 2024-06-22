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
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"

#include "Communication/Communication.hpp"
#include "MainProgram/Arguments.hpp"

int main(int ac, char **av)
{
    try {
        zappy::Arguments args({av + 1, av + ac});
        zappy::Communication server(args.port, args.ip);
        server.connect();
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
