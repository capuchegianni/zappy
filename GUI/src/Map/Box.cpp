/*
** EPITECH PROJECT, 2024
** Box.cpp
** File description:
** zappy_gui
*/

#include "Box.hpp"

zappy::BoxDrawables::BoxDrawables(zappy::render3d::DisplayTile &displayTile, zappy::render3d::Camera &camera, std::size_t x, std::size_t y) : _tile(displayTile), _camera(camera), _x(x), _y(y)
{
}

void zappy::BoxDrawables::updateSprite()
{
    sprite = sf::Sprite(_tile.getTexture());
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setPosition(_camera.displayUnitaryX.x * _x + _camera.displayUnitaryY.x * _y + _camera.centerX * _camera.displayUnitaryX.x + _camera.displayUnitaryY.x * _camera.centerY + _camera.displayUnitaryZ.x * _camera.centerZ,
                        _camera.displayUnitaryX.y * _x + _camera.displayUnitaryY.y * _y + _camera.centerX * _camera.displayUnitaryX.y + _camera.displayUnitaryY.y * _camera.centerY + _camera.displayUnitaryZ.y * _camera.centerZ);
}

zappy::BoxDrawables::~BoxDrawables() = default;

zappy::Box::Box(std::size_t x, std::size_t y, zappy::SceneData &data) : x(x), y(y), _drawables(*data.getRandomTile(), data.camera, x, y)
{
    food = 0;
    linemate = 0;
    deraumere = 0;
    sibur = 0;
    mendiane = 0;
    phiras = 0;
    thystame = 0;
}

zappy::Box::~Box() = default;

void zappy::Box::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.sprite, states);
}

void zappy::Box::updateSprite()
{
    _drawables.updateSprite();
}
