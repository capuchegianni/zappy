/*
** EPITECH PROJECT, 2024
** Map.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Box.hpp"
#include "../Display/Assets.hpp"
#include "../Characters/Team.hpp"

namespace zappy
{
    class MapDrawables
    {
        public:
            MapDrawables();
            ~MapDrawables();

            sf::RectangleShape background;
    };

    class Map : public sf::Drawable
    {
        public:
            Map(Assets &assets);
            Map(std::size_t width, std::size_t height, Assets &assets);
            ~Map() override;

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
            void addPlayer(const std::shared_ptr<Trantorien>& player, std::string &team);
            void removePlayerById(std::size_t id);
            void movePlayerById(std::size_t x, std::size_t y, std::size_t id);

            void addEgg(std::size_t x, std::size_t y, std::size_t id, std::string &team);
            void removeEggById(std::size_t id);

            Team &getTeam(std::string &name);
            void addTeam(std::string &name);

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);

            void updateDisplay();

        private:
            std::vector<std::vector<Box>> _map;
            std::size_t _getPlayerIndexById(std::size_t id);

            Assets &_assets;

            MapDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            std::vector<Team> _teams = {};
    };
}
