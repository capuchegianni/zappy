/*
** EPITECH PROJECT, 2024
** Map.cpp
** File description:
** zappy_gui
*/

#include "Map.hpp"

zappy::Map::Map(std::size_t width, std::size_t height)
{
    for (std::size_t i = 0; i < width; i++) {
        _map.emplace_back();
        for (std::size_t j = 0; j < height; j++) {
            _map[i].emplace_back();
        }
    }
}

zappy::Map::~Map() = default;

zappy::Box &zappy::Map::operator()(int x, int y)
{
    if (x < 0 || y < 0 || x >= _map.size() || y >= _map[0].size())
        throw Map::MapError("Out of bounds");

    return _map[x][y];
}

std::shared_ptr<zappy::Trantorien> zappy::Map::getPlayerById(std::size_t id)
{
    for (auto &player : _players) {
        if (player->id == id)
            return player;
    }

    throw Map::MapError("Player not found");
}

void zappy::Map::addPlayer(std::shared_ptr<Trantorien> player)
{
    _players.push_back(player);
}

void zappy::Map::removePlayerById(std::size_t id)
{
    std::shared_ptr<Trantorien> player = getPlayerById(id);

    if (player != nullptr) {
        _players.erase(_players.begin() + _getPlayerIndexById(id));
    }
}

std::size_t zappy::Map::_getPlayerIndexById(std::size_t id)
{
    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i]->id == id)
            return i;
    }

    throw Map::MapError("Player not found");
}
