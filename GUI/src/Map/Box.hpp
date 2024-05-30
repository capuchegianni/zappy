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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Characters/Trantorien.hpp"

namespace zappy
{
    class BoxDrawables
    {
        public:
            BoxDrawables();
            ~BoxDrawables();

            class BoxDrawablesError : public std::exception
            {
                public:
                    BoxDrawablesError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            sf::RectangleShape background;

            sf::Text food = sf::Text();
            sf::Text linemate = sf::Text();
            sf::Text deraumere = sf::Text();
            sf::Text sibur = sf::Text();
            sf::Text mendiane = sf::Text();
            sf::Text phiras = sf::Text();
            sf::Text thystame = sf::Text();

        private:
            sf::Font _font;
    };

    class Box : public sf::Drawable
    {
        public:
            Box(std::size_t x, std::size_t y);
            ~Box() override;

            class BoxError : public std::exception
            {
                public:
                    BoxError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);
            void updateText();

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            std::size_t x = 0;
            std::size_t y = 0;

            void addPlayer(const std::shared_ptr<Trantorien>& player);
            void removePlayerById(std::size_t id);
        private:
            std::vector<std::shared_ptr<Trantorien>> _players = {};
            std::size_t _getPlayerIndexById(std::size_t id);

            BoxDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
