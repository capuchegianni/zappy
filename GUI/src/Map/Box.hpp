/*
** EPITECH PROJECT, 2024
** Box.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>
#include <vector>
#include <memory>
#include "../Characters/Trantorien.hpp"

namespace zappy
{
    class Box
    {
        public:
            Box();

            ~Box();

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            std::vector<std::shared_ptr<Trantorien>> players = {};
    };
}
