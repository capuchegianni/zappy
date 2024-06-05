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
    sf::Vector2<unsigned int> size = _drawables.texture.getSize();

    math::Point3D topLeft = camera.projectPoint(math::Point3D(0, 0, 0));
    math::Point3D topRight = camera.projectPoint(math::Point3D(size.x, 0, 0));
    math::Point3D bottomLeft = camera.projectPoint(math::Point3D(0, size.y, 0));
    math::Point3D bottomRight = camera.projectPoint(math::Point3D(size.x, size.y, 0));

    std::cout << topLeft << std::endl;
    std::cout << topRight << std::endl;
    std::cout << bottomLeft << std::endl;
    std::cout << bottomRight << std::endl;

    // create a new texture with the projected corners
    sf::Image image;
}

void zappy::render3d::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}
