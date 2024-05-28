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
#include <string>
#include "../Characters/Trantorien.hpp"

namespace zappy
{
    class Box
    {
        public:
            Box();
            ~Box();

            class BoxError : public std::exception
            {
                public:
                    BoxError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            void addPlayer(const std::shared_ptr<Trantorien>& player);
            void removePlayerById(std::size_t id);
        private:
            std::vector<std::shared_ptr<Trantorien>> _players = {};
            std::size_t _getPlayerIndexById(std::size_t id);
    };
}
