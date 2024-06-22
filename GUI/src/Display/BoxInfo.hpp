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
#include "../Map/Box.hpp"

namespace zappy
{
    class BoxInfoDrawables
    {
        public:
            BoxInfoDrawables();
            ~BoxInfoDrawables();

            void updateDisplay(std::shared_ptr<Box> &box);

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

            sf::Text foodText;
            sf::Text linemateText;
            sf::Text deraumereText;
            sf::Text siburText;
            sf::Text mendianeText;
            sf::Text phirasText;
            sf::Text thystameText;

            sf::Text title;
    };

    class BoxInfo : public sf::Drawable
    {
        public:
            BoxInfo(Assets &assets);
            ~BoxInfo();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);
            void updateDisplay();

            void setBox(std::shared_ptr<Box> box);

        private:
            BoxInfoDrawables _drawables;

            std::shared_ptr<Box> _box;

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
