/*
** EPITECH PROJECT, 2024
** PlayerInfo.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Characters/Trantorien.hpp"
#include "../Display/Assets.hpp"

namespace zappy
{
    class PlayerInfoDrawables
    {
        public:
            PlayerInfoDrawables();
            ~PlayerInfoDrawables();

            void updateDisplay(std::shared_ptr<Trantorien> &player);

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

            sf::Text playerID;
            sf::Text playerLevel;
            sf::Text playerOrientation;
            sf::Text playerPosition;
    };

    class PlayerInfo : public sf::Drawable
    {
        public:
            PlayerInfo(Assets &assets);
            ~PlayerInfo();

            void setDisplaySize(sf::Vector2f &size);
            void setDisplayPosition(sf::Vector2f &position);
            void updateDisplay();

            void setPlayer(std::shared_ptr<Trantorien> &player);

        private:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            std::shared_ptr<Trantorien> _player;
            PlayerInfoDrawables _drawables;
    };
}
