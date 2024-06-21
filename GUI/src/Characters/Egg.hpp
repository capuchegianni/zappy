/*
** EPITECH PROJECT, 2024
** Egg.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../Display/Renderer/Camera.hpp"

namespace zappy
{
    class EggDrawables
    {
        public:
            EggDrawables();
            ~EggDrawables();

            std::shared_ptr<sf::Texture> texture;
            sf::Sprite sprite;
            sf::CircleShape shadow;
    };

    class Egg : public sf::Drawable
    {
        public:
            Egg(std::size_t x, std::size_t y, std::size_t id, std::string);
            ~Egg();

            void updateDisplay(render3d::Camera &camera);
            void setTexture(const std::shared_ptr<sf::Texture> &texture);
            std::pair<double, sf::Sprite> getSprite(render3d::Camera &camera);

            std::string team;
            std::size_t id;

            std::size_t x = 0;
            std::size_t y = 0;
        private:
            EggDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
