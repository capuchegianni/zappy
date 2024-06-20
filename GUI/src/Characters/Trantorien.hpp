/*
** EPITECH PROJECT, 2024
** Trantorien.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "../Display/Renderer/Camera.hpp"

namespace zappy
{
    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    class TrantorienDrawables
    {
        public:
            TrantorienDrawables();
            ~TrantorienDrawables();

            sf::CircleShape body;
            sf::CircleShape head;
            sf::CircleShape shadow;
    };

    class Trantorien : public sf::Drawable
    {
        public:
            Trantorien(std::size_t id = 0);

            ~Trantorien() override;

            void updateDisplay(render3d::Camera &camera);

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            std::size_t level = 0;
            std::size_t id;

            short direction = 0;

            std::size_t x = 0;
            std::size_t y = 0;

            std::string team;
            sf::Color color;
        private:
            TrantorienDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
