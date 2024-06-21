/*
** EPITECH PROJECT, 2024
** Egg.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <string>

namespace zappy
{
    class Egg
    {
        public:
            Egg(std::size_t x, std::size_t y, std::size_t id, std::string team);
            ~Egg();

            std::string team;
            std::size_t id;

            std::size_t x = 0;
            std::size_t y = 0;
    };
}
