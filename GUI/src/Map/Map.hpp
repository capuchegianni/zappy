/*
** EPITECH PROJECT, 2024
** Map.hpp
** File description:
** zappy_gui
*/

#pragma once

namespace zappy
{
    class Map
    {
        public:
            Map();

            ~Map();

            void operator()(int x, int y) const;

        private:
    };
}
