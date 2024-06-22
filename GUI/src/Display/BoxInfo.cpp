/*
** EPITECH PROJECT, 2024
** BoxInfo.cpp
** File description:
** zappy_gui
*/

#include "BoxInfo.hpp"

zappy::BoxInfoDrawables::BoxInfoDrawables()
{
    rect.setFillColor(sf::Color::Green);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(4);
}

zappy::BoxInfoDrawables::~BoxInfoDrawables() = default;

void zappy::BoxInfoDrawables::updateDisplay()
{
}

void zappy::BoxInfo::setDisplaySize(sf::Vector2f &size)
{
    this->_drawables.rect.setSize(size);
}

void zappy::BoxInfo::setDisplayPosition(sf::Vector2f &position)
{
    this->_drawables.rect.setPosition(position);
}

void zappy::BoxInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->_drawables.rect, states);
}

zappy::BoxInfo::BoxInfo() = default;

zappy::BoxInfo::~BoxInfo() = default;
