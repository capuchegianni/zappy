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

    if (!_font.loadFromFile("../assets/fonts/Minecraft.ttf"))
        throw BoxDrawables::BoxDrawablesError("Could not load font");

    food.setFont(_font);
    linemate.setFont(_font);
    deraumere.setFont(_font);
    sibur.setFont(_font);
    mendiane.setFont(_font);
    phiras.setFont(_font);
    thystame.setFont(_font);

    food.setCharacterSize(10);
    linemate.setCharacterSize(10);
    deraumere.setCharacterSize(10);
    sibur.setCharacterSize(10);
    mendiane.setCharacterSize(10);
    phiras.setCharacterSize(10);
    thystame.setCharacterSize(10);

    food.setFillColor(sf::Color::Black);
    linemate.setFillColor(sf::Color::Black);
    deraumere.setFillColor(sf::Color::Black);
    sibur.setFillColor(sf::Color::Black);
    mendiane.setFillColor(sf::Color::Black);
    phiras.setFillColor(sf::Color::Black);
    thystame.setFillColor(sf::Color::Black);
}

zappy::BoxDrawables::~BoxDrawables() = default;

zappy::Box::Box(std::size_t x, std::size_t y) : x(x), y(y) {}

zappy::Box::~Box() = default;

void zappy::Box::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);

    _drawables.food.setCharacterSize(size.y / 10);
    _drawables.linemate.setCharacterSize(size.y / 10);
    _drawables.deraumere.setCharacterSize(size.y / 10);
    _drawables.sibur.setCharacterSize(size.y / 10);
    _drawables.mendiane.setCharacterSize(size.y / 10);
    _drawables.phiras.setCharacterSize(size.y / 10);
    _drawables.thystame.setCharacterSize(size.y / 10);
}

void zappy::Box::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);
}

void zappy::Box::updateText()
{
    _drawables.food.setString(std::to_string(food));
    _drawables.linemate.setString(std::to_string(linemate));
    _drawables.deraumere.setString(std::to_string(deraumere));
    _drawables.sibur.setString(std::to_string(sibur));
    _drawables.mendiane.setString(std::to_string(mendiane));
    _drawables.phiras.setString(std::to_string(phiras));
    _drawables.thystame.setString(std::to_string(thystame));
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

    target.draw(_drawables.food, states);
    target.draw(_drawables.linemate, states);
    target.draw(_drawables.deraumere, states);
    target.draw(_drawables.sibur, states);
    target.draw(_drawables.mendiane, states);
    target.draw(_drawables.phiras, states);
    target.draw(_drawables.thystame, states);
}
