/*
** EPITECH PROJECT, 2024
** Map.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <string>
#include "Box.hpp"

namespace zappy
{
    class Map
    {
        public:
            Map(std::size_t width = 10, std::size_t height = 10);

            ~Map();

            class MapError : public std::exception
            {
                public:
                    MapError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

             Box &operator()(std::size_t x, std::size_t y);
             std::shared_ptr<Trantorien> getPlayerById(std::size_t id);
             void addPlayer(std::shared_ptr<Trantorien> player);
             void removePlayerById(std::size_t id);

        private:
            std::vector<std::vector<Box>> _map;
            std::vector<std::shared_ptr<Trantorien>> _players = {};
            std::size_t _getPlayerIndexById(std::size_t id);
    };
}
