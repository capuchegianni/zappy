/*
** EPITECH PROJECT, 2024
** Broadcast.cpp
** File description:
** zappy_gui
*/

#include "Broadcast.hpp"

zappy::BroadcastDrawables::BroadcastDrawables() = default;

zappy::BroadcastDrawables::~BroadcastDrawables() = default;

zappy::Broadcast::Broadcast(double duration, double x, double y, double z, sf::Color color, const std::string &message, Assets &assets) : x(x), y(y), z(z), duration(duration)
{
    _drawables.circle.setFillColor(sf::Color::Transparent);
    _drawables.circle.setOutlineColor(color);
    _drawables.circle.setOutlineThickness(5);
    _drawables.circle.setScale(1, 0.7);
}

zappy::Broadcast::~Broadcast() = default;

void zappy::Broadcast::updateDisplay(zappy::render3d::Camera &camera)
{
    _drawables.circle.setRadius(_drawables.clock.getElapsedTime().asSeconds() * camera.unitaryPixelsSize * 5);
    _drawables.circle.setOrigin(_drawables.circle.getRadius(), _drawables.circle.getRadius());
    _drawables.circle.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                 camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ - z);
}

double zappy::Broadcast::getElapsedTimeSeconds() const
{
    return _drawables.clock.getElapsedTime().asSeconds();
}

void zappy::Broadcast::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.circle, states);
}
