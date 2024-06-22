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

            sf::RectangleShape rect;
    };

    class BoxInfo : public sf::Drawable
    {
        public:
            BoxInfo();
            ~BoxInfo();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);

        private:
            BoxInfoDrawables _drawables;

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
