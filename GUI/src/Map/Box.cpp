/*
** EPITECH PROJECT, 2024
** Box.cpp
** File description:
** zappy_gui
*/

#include "Box.hpp"

zappy::BoxDrawables::BoxDrawables()
{
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(1);
}

zappy::BoxDrawables::~BoxDrawables() = default;

zappy::Box::Box(std::size_t x, std::size_t y) : x(x), y(y) {}

zappy::Box::~Box() = default;

void zappy::Box::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);
}

void zappy::Box::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
}

void zappy::Box::addPlayer(const std::shared_ptr<Trantorien>& player)
{
    _players.push_back(player);
}

void zappy::Box::removePlayerById(std::size_t id)
{
    std::size_t index = _getPlayerIndexById(id);

    _players.erase(_players.begin() + index);

    if (_players.empty())
        throw Box::BoxError("No more players in this box");
}

std::size_t zappy::Box::_getPlayerIndexById(std::size_t id)
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i]->id == id)
            return i;
    }

    throw Box::BoxError("Player not found");
}

void zappy::Box::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.background, states);
}
