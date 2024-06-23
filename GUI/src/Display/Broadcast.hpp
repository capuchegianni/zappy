/*
** EPITECH PROJECT, 2024
** Broadcast.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include <string>

#include "Assets.hpp"

namespace zappy
{
    class BroadcastDrawables
    {
        public:
            BroadcastDrawables();
            ~BroadcastDrawables();

            sf::Clock clock;
            sf::Sprite background;
            sf::Sprite leftSide;
            sf::Sprite rightSide;
            sf::Sprite center;
            sf::Sprite fill1;
            sf::Sprite fill2;
            sf::Text message;

            sf::View view;

            sf::RenderTexture renderTexture;
            sf::Sprite sprite;

            double duration;
    };

    class Broadcast : public sf::Drawable
    {
        public:
            Broadcast(double duration, std::size_t x, std::size_t y, const std::string &message, Assets &assets);
            ~Broadcast();

            void updateDisplay(render3d::Camera &camera);

            double getElapsedTimeSeconds() const;

            std::size_t x;
            std::size_t y;

        private:
            BroadcastDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
