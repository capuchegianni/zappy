/*
** EPITECH PROJECT, 2024
** Tile.cpp
** File description:
** zappy_gui
*/

#include "Tile.hpp"

zappy::render3d::TileDrawables::TileDrawables(sf::Texture &texture) : texture(texture) {}

zappy::render3d::TileDrawables::~TileDrawables() = default;

zappy::render3d::Tile::Tile(Assets &assets) : _drawables(assets.placeholderTexture) {}

zappy::render3d::Tile::~Tile() = default;

void zappy::render3d::Tile::update(zappy::Box &box)
{
    x = box.x;
    y = box.y;
}

void zappy::render3d::Tile::setTileTexture(sf::Texture &texture)
{
    _drawables.displayTexture = texture;
}

void zappy::render3d::Tile::computeTileImage(zappy::render3d::Camera &camera)
{
    // project tile corners to screen


}
