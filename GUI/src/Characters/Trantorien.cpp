/*
** EPITECH PROJECT, 2024
** Trantorien.cpp
** File description:
** zappy_gui
*/

#include <iostream>
#include "Trantorien.hpp"

zappy::TrantorienDrawables::TrantorienDrawables()
{
    head.setFillColor(sf::Color::Transparent);

    body.setRadius(50);

    body.setOrigin(body.getGlobalBounds().width / 2, body.getGlobalBounds().height / 2);
    body.setScale(1, 2);

    body.setOutlineColor(sf::Color::Black);
    body.setOutlineThickness(2);

    shadow.setFillColor(sf::Color(0, 0, 0, 70));
    shadow.setRadius(50);
    shadow.setOrigin(shadow.getGlobalBounds().width / 2, shadow.getGlobalBounds().height / 2);
    shadow.setScale(1, 0.7);
}

zappy::TrantorienDrawables::~TrantorienDrawables() = default;

zappy::Trantorien::Trantorien(std::size_t id) : id(id) {}

zappy::Trantorien::~Trantorien() = default;

void zappy::Trantorien::updateDisplay(zappy::render3d::Camera &camera)
{
    _drawables.body.setFillColor(color);
    _drawables.body.setRadius(camera.unitaryPixelsSize / 2);
    _drawables.body.setOrigin(_drawables.body.getGlobalBounds().width / 2, _drawables.body.getGlobalBounds().height / 2);
    _drawables.body.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
    _drawables.shadow.setRadius(camera.unitaryPixelsSize / 2);
    _drawables.shadow.setOrigin(_drawables.shadow.getGlobalBounds().width / 2, _drawables.shadow.getGlobalBounds().height / 2);
    _drawables.shadow.setPosition(camera.displayUnitaryX.x * x + camera.displayUnitaryY.x * y + camera.centerX * camera.displayUnitaryX.x + camera.displayUnitaryY.x * camera.centerY + camera.displayUnitaryZ.x * camera.centerZ,
                                  camera.displayUnitaryX.y * x + camera.displayUnitaryY.y * y + camera.centerX * camera.displayUnitaryX.y + camera.displayUnitaryY.y * camera.centerY + camera.displayUnitaryZ.y * camera.centerZ);
}

void zappy::Trantorien::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.shadow, states);
    target.draw(_drawables.body, states);
}
