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
#include "../Display/Renderer/Camera.hpp"

namespace zappy
{
    class BroadcastDrawables
    {
        public:
            BroadcastDrawables();
            ~BroadcastDrawables();

            sf::Clock clock;
            sf::Sprite leftSide;
            sf::Sprite rightSide;
            sf::Sprite center;
            sf::Sprite fill1;
            sf::Sprite fill2;
            sf::Text message;

            sf::View view;

            sf::RenderTexture renderTexture;
            sf::Sprite sprite;

    };

    class Broadcast : public sf::Drawable
    {
        public:
            Broadcast(double duration, double x, double y, double z, const std::string &message, Assets &assets);
            ~Broadcast();

            void updateDisplay(render3d::Camera &camera);

            double getElapsedTimeSeconds() const;

            std::pair<double, sf::Sprite> getSprite(render3d::Camera &camera);

            std::size_t x;
            std::size_t y;
            std::size_t z;

            double duration;

        private:
            BroadcastDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
