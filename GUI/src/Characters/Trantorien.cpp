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
    body.setFillColor(sf::Color::Green);
    head.setFillColor(sf::Color::Red);
}

zappy::TrantorienDrawables::~TrantorienDrawables() = default;

zappy::Trantorien::Trantorien(std::size_t id) : id(id) {}

zappy::Trantorien::~Trantorien() = default;

void zappy::Trantorien::setDisplaySize(sf::Vector2f &size)
{
    float minSize = size.x < size.y ? size.x : size.y;

    _drawables.body.setRadius(minSize / 2);
    _drawables.head.setRadius(minSize / 10);
}

void zappy::Trantorien::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.body.setPosition(position);

    sf::Vector2f headPosition = position + sf::Vector2f(_drawables.body.getRadius() - _drawables.head.getRadius(), _drawables.body.getRadius() - _drawables.head.getRadius());

    switch (direction) {
        case UP:
            headPosition.y -= _drawables.body.getRadius() / 1.5f;
            break;
        case RIGHT:
            headPosition.x += _drawables.body.getRadius() / 1.5f;
            break;
        case DOWN:
            headPosition.y += _drawables.body.getRadius() / 1.5f;
            break;
        case LEFT:
            headPosition.x -= _drawables.body.getRadius() / 1.5f;
            break;
    }

    _drawables.head.setPosition(headPosition);
}

void zappy::Trantorien::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.body, states);
    target.draw(_drawables.head, states);
}
