/*
** EPITECH PROJECT, 2024
** Tile.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Camera.hpp"
#include "../Assets.hpp"
#include "../../Map/Box.hpp"

#include "../../../include/Math/Ray3D.hpp"

namespace zappy
{
    namespace render3d
    {
        class TileDrawables
        {
            public:
                TileDrawables(sf::Texture &texture);
                ~TileDrawables();

                sf::Texture &texture;
                sf::Texture displayTexture;
                sf::Sprite sprite;
        };

        class Tile : public sf::Drawable
        {
            public:
                Tile(Assets &assets);
                ~Tile();

                void update(Box &box);

                void setTileTexture(sf::Texture &texture);
                void computeTileImage(Camera &camera);

                std::size_t x;
                std::size_t y;

            private:
                TileDrawables _drawables;

                void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}
