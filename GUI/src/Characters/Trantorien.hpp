/*
** EPITECH PROJECT, 2024
** Trantorien.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>
#include <memory>
#include <iostream>
#include <functional>
#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../Display/Renderer/Camera.hpp"

namespace zappy
{
    enum Direction
    {
        UP = 1,
        LEFT,
        DOWN,
        RIGHT,
    };

    enum CamDirection
    {
        TOWARDS,
        AWAY,
        LEFTC,
        RIGHTC
    };

    class TrantorienDrawables
    {
        public:
            TrantorienDrawables();
            ~TrantorienDrawables();

            sf::Sprite body;
            sf::CircleShape shadow;

            std::shared_ptr<sf::Texture> towardsCamera;
            std::shared_ptr<sf::Texture> awayFromCamera;
            std::shared_ptr<sf::Texture> left;
            std::shared_ptr<sf::Texture> right;
    };

    class Trantorien : public sf::Drawable
    {
        public:
            Trantorien(std::size_t id = 0);

            ~Trantorien() override;

            void updateDisplay(render3d::Camera &camera);
            void setTextures(std::shared_ptr<sf::Texture> &towardsCamera, std::shared_ptr<sf::Texture> &awayFromCamera, std::shared_ptr<sf::Texture> &left, std::shared_ptr<sf::Texture> &right);

            static CamDirection getDirectionForCam(render3d::Camera &camera, short direction);

            sf::Sprite &getSprite() { return _drawables.body; }

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

            CamDirection directionForCam = TOWARDS;

        private:
            TrantorienDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
