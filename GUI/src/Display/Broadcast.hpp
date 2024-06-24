/*
** EPITECH PROJECT, 2024
** Broadcast.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
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

            sf::CircleShape circle;
            sf::Clock clock;
    };

    class Broadcast : public sf::Drawable
    {
        public:
            Broadcast(double duration, double x, double y, double z, sf::Color color, const std::string &message, Assets &assets);
            ~Broadcast();

            void updateDisplay(render3d::Camera &camera);

            double getElapsedTimeSeconds() const;

            std::size_t x;
            std::size_t y;
            std::size_t z;

            double duration;

        private:
            BroadcastDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
