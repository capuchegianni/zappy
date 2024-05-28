/*
** EPITECH PROJECT, 2024
** Box.cpp
** File description:
** zappy_gui
*/

#include "Box.hpp"

zappy::Box::Box() = default;

zappy::Box::~Box() = default;

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
