/*
** EPITECH PROJECT, 2024
** Team.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <memory>
#include <vector>
#include <random>
#include <string>

#include "../Display/Assets.hpp"
#include "Trantorien.hpp"
#include "Egg.hpp"

namespace zappy
{
    class Team
    {
        public:
            Team(std::string &name, Assets &assets);
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

            static sf::Color generateColor(const std::string &name);

            static std::shared_ptr<sf::Texture> recolorTexture(const sf::Texture &texture, const sf::Color &color);

            std::string name;
            std::vector<std::shared_ptr<Trantorien>> players = {};
            std::vector<std::shared_ptr<Egg>> eggs = {};
            sf::Color color;

            std::shared_ptr<sf::Texture> towardsCameraTexture;
            std::shared_ptr<sf::Texture> towardsLeftTexture;
            std::shared_ptr<sf::Texture> towardsRightTexture;
            std::shared_ptr<sf::Texture> towardsBackTexture;
            std::shared_ptr<sf::Texture> eggTexture;
    };
}
