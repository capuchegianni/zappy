/*
** EPITECH PROJECT, 2024
** BoxInfo.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Assets.hpp"

namespace zappy
{
    class BoxInfoDrawables
    {
        public:
            BoxInfoDrawables();
            ~BoxInfoDrawables();

            void updateDisplay();

            sf::RectangleShape background;
            sf::RenderTexture renderTexture;
            sf::Sprite sprite;
            sf::View view;

            sf::Sprite food;
            sf::Sprite linemate;
            sf::Sprite deraumere;
            sf::Sprite sibur;
            sf::Sprite mendiane;
            sf::Sprite phiras;
            sf::Sprite thystame;
    };

    class BoxInfo : public sf::Drawable
    {
        public:
            BoxInfo(Assets &assets);
            ~BoxInfo();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);
            void updateDisplay();

        private:
            BoxInfoDrawables _drawables;

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
