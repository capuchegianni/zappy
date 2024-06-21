/*
** EPITECH PROJECT, 2024
** Team.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Trantorien.hpp"
#include "Egg.hpp"

namespace zappy
{
    class Team
    {
        public:
            Team(std::string &name);
            ~Team();

            class TeamError : public std::exception
            {
                public:
                    TeamError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            void addPlayer(const std::shared_ptr<Trantorien>& player);
            void removePlayerById(std::size_t id);
            std::shared_ptr<Trantorien> getPlayerById(std::size_t id);
            std::size_t getPlayerIndexById(std::size_t id);

            void addEgg(const std::shared_ptr<Egg>& egg);
            void removeEggById(std::size_t id);

            std::string name;
            std::vector<std::shared_ptr<Trantorien>> players = {};
            std::vector<std::shared_ptr<Egg>> eggs = {};
        private:
    };
}
