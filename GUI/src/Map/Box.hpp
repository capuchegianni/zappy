/*
** EPITECH PROJECT, 2024
** Box.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <cstddef>
#include <vector>
#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector3.hpp>

#include "../Characters/Trantorien.hpp"
#include "../Display/Renderer/DisplayTile.hpp"
#include "../Display/SceneData.hpp"

namespace zappy
{
    class BoxDrawables
    {
        public:
            BoxDrawables(render3d::DisplayTile &displayTile, Assets &assets, render3d::Camera &camera, std::size_t x, std::size_t y);
            ~BoxDrawables();

            class BoxDrawablesError : public std::exception
            {
                public:
                    BoxDrawablesError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            sf::Vector3f getRandomPosInBox();

            void updateSprite();
            sf::Sprite sprite;

            sf::Sprite food;
            sf::Sprite linemate;
            sf::Sprite deraumere;
            sf::Sprite sibur;
            sf::Sprite mendiane;
            sf::Sprite phiras;
            sf::Sprite thystame;

            sf::Vector3f foodPosition;
            sf::Vector3f linematePosition;
            sf::Vector3f deraumerePosition;
            sf::Vector3f siburPosition;
            sf::Vector3f mendianePosition;
            sf::Vector3f phirasPosition;
            sf::Vector3f thystamePosition;

            Assets &_assets;

        private:
            render3d::DisplayTile &_tile;
            render3d::Camera &_camera;

            std::size_t _x;
            std::size_t _y;
    };

    class Box : public sf::Drawable
    {
        public:
            Box(std::size_t x, std::size_t y, SceneData &data, Assets &assets);
            ~Box() override;

            class BoxError : public std::exception
            {
                public:
                    BoxError(std::string const &message) : _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

            void updateSprite();

            std::size_t food = 0;
            std::size_t linemate = 0;
            std::size_t deraumere = 0;
            std::size_t sibur = 0;
            std::size_t mendiane = 0;
            std::size_t phiras = 0;
            std::size_t thystame = 0;

            std::size_t x = 0;
            std::size_t y = 0;

            std::vector<std::pair<double, sf::Sprite>> getObjectsSprites(render3d::Camera &camera);

        private:
            BoxDrawables _drawables;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}
