/*
** EPITECH PROJECT, 2024
** Arguments.cpp
** File description:
** zappy_gui
*/

#include "Arguments.hpp"

zappy::Arguments::Arguments(std::vector<std::string> args)
{
    if (args.size() != 4) {
        throw ArgumentsError("Invalid number of arguments.");
    }

    int i = 0;

    for (auto arg : args)
    {
        if (arg == "-p")
        {
            port = std::stoi(args[i + 1]);
        }
        else if (arg == "-h")
        {
            ip = args[i + 1];
        }

        i++;
    }

    if (ip == " ")
    {
        throw ArgumentsError("No IP address provided.");
    }

    if (port == -1)
    {
        throw ArgumentsError("No port provided");
    }
}

zappy::Arguments::~Arguments()
{
}