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

            std::size_t food;
            std::size_t linemate;
            std::size_t deraumere;
            std::size_t sibur;
            std::size_t mendiane;
            std::size_t phiras;
            std::size_t thystame;

            std::vector<std::shared_ptr<Trantorien>> players;
    };
}
