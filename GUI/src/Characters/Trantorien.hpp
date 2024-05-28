/*
** EPITECH PROJECT, 2024
** Trantorien.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>

namespace zappy
{
    enum class Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    class Trantorien
    {
        public:
            Trantorien(std::size_t id = 0);

            ~Trantorien();

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            std::size_t level = 0;

            std::size_t id;

            short direction = 0;

            std::size_t x = 0;
            std::size_t y = 0;
    };
}
