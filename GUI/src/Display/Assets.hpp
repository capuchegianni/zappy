/*
** EPITECH PROJECT, 2024
** Assets.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Font.hpp>

namespace zappy
{
    class Assets
    {
        public:
            Assets();
            ~Assets();

            class AssetsError : public std::exception
            {
                public:
                    AssetsError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            sf::Font font;
    };
}
