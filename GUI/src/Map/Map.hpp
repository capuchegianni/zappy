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
#include <SFML/Graphics/CircleShape.hpp>
#include "Box.hpp"

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
            Map();
            Map(std::size_t width, std::size_t height);
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
             void addPlayer(const std::shared_ptr<Trantorien>& player);
             void removePlayerById(std::size_t id);
             void movePlayerById(std::size_t x, std::size_t y, std::size_t id);

             void setMapDisplaySize(sf::Vector2f &size);
             void setMapDisplayPosition(sf::Vector2f &position);
        private:
            std::vector<std::vector<Box>> _map;
            std::vector<std::shared_ptr<Trantorien>> _players = {};
            std::size_t _getPlayerIndexById(std::size_t id);

            MapDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
