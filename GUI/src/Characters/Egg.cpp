/*
** EPITECH PROJECT, 2024
** Egg.cpp
** File description:
** zappy_gui
*/

#include "Egg.hpp"

zappy::EggDrawables::EggDrawables()
{
    shadow.setFillColor(sf::Color(0, 0, 0, 70));
}

zappy::EggDrawables::~EggDrawables() = default;

zappy::Egg::Egg(std::size_t x, std::size_t y, std::size_t id, std::string team) : team(team), id(id), x(x), y(y) {}

zappy::Egg::~Egg() = default;

void zappy::Egg::updateDisplay(render3d::Camera &camera)
{
    double scaleFromTile = 0.45;

    float scale = (camera.unitaryPixelsSize * scaleFromTile) / _drawables.sprite.getTexture()->getSize().x;

    _drawables.sprite.setOrigin(_drawables.sprite.getTexture()->getSize().x / 2, _drawables.sprite.getTexture()->getSize().y);
    _drawables.sprite.setScale(scale, scale);
    _drawables.sprite.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
    _drawables.shadow.setRadius(camera.unitaryPixelsSize / 4);
    _drawables.shadow.setOrigin(camera.unitaryPixelsSize / 4, camera.unitaryPixelsSize / 4);
    _drawables.shadow.setScale(1, 0.7);
    _drawables.shadow.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
}

void zappy::Egg::setTexture(const std::shared_ptr<sf::Texture> &texture)
{
    _drawables.sprite.setTexture(*texture);
}

std::pair<double, sf::Sprite> zappy::Egg::getSprite(render3d::Camera &camera)
{
    math::Point3D CameraPosition = math::Vector3D(camera.centerX - camera.direction.x * 10000, camera.centerY - camera.direction.y * 10000, camera.centerZ - camera.direction.z * 10000);

    return {math::Point3D::distance(CameraPosition, math::Vector3D(x, y, 0)), _drawables.sprite};
}

void zappy::Egg::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.shadow, states);
}
