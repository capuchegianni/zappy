/*
** EPITECH PROJECT, 2024
** Map.cpp
** File description:
** zappy_gui
*/

#include "Map.hpp"

zappy::MapDrawables::MapDrawables(zappy::Assets &assets, math::Vector3D mapSize) : sceneData(assets)
{
    sceneData.camera.rotate(math::Vector3D(-45, 0, -45));
    sceneData.camera.centerX = -mapSize.x / 2;
    sceneData.camera.centerY = -mapSize.y / 2;
    sceneData.camera.centerZ = mapSize.z / 2;
}

void zappy::MapDrawables::updateDisplay()
{
    for (auto &tile : sceneData.tiles) {
        tile->computeTileImage(sceneData.camera);
    }
}

zappy::MapDrawables::~MapDrawables() = default;

zappy::Map::Map(Assets &assets) : Map(10, 10, assets) {}

zappy::Map::Map(std::size_t width, std::size_t height, Assets &assets) : sceneDate(assets, math::Vector3D(width, height, 0)), _assets(assets)
{
    _map.reserve(width);

    for (std::size_t i = 0; i < width; i++)
    {
        _map.push_back({});
        _map[i].reserve(height);

        for (std::size_t j = 0; j < height; j++)
        {
            _map[i].push_back(Box(i, j, sceneDate.sceneData));
        }
    }
}

zappy::Map::~Map() = default;

zappy::Box &zappy::Map::operator()(std::size_t x, std::size_t y)
{
    if (x >= _map.size() || y >= _map[0].size())
        throw Map::MapError("Out of bounds");

    return _map[x][y];
}

std::shared_ptr<zappy::Trantorien> zappy::Map::getPlayerById(std::size_t id)
{
    for (auto &team : _teams) {
        try {
            return team.getPlayerById(id);
        } catch (Team::TeamError &e) {
            continue;
        }
    }

    throw Map::MapError("Player " + std::to_string(id) + " not found");
}

void zappy::Map::addPlayer(const std::shared_ptr<Trantorien>& player, std::string &team)
{
    Team &storedTeam = getTeam(team);
    player->team = team;
    storedTeam.addPlayer(player);
}

void zappy::Map::removePlayerById(std::size_t id)
{
    std::shared_ptr<Trantorien> player = getPlayerById(id);
    zappy::Team &team = getTeam(player->team);

    _map[player->x][player->y].removePlayerById(id);
    team.removePlayerById(id);
}

std::size_t zappy::Map::_getPlayerIndexById(std::size_t id)
{
    std::shared_ptr<zappy::Trantorien> player = getPlayerById(id);
    zappy::Team &team = getTeam(getPlayerById(id)->team);

    return team.getPlayerIndexById(id);
}

void zappy::Map::movePlayerById(std::size_t x, std::size_t y, std::size_t id)
{
    std::shared_ptr<Trantorien> player = getPlayerById(id);

    if (player == nullptr)
        throw Map::MapError("Player not found");

    _map[x][y].addPlayer(player);
    _map[player->x][player->y].removePlayerById(id);

    player->x = x;
    player->y = y;
}

void zappy::Map::updateDisplay()
{
    sceneDate.updateDisplay();

    for (auto &row : _map) {
        for (auto &box : row) {
            box.updateSprite();
        }
    }
}

void zappy::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &row : _map) {
        for (auto &box : row) {
            target.draw(box, states);
        }
    }

    for (auto &team : _teams)
    {
        for (auto &player: team.players)
        {
            target.draw(*player, states);
        }
    }
}

zappy::Team &zappy::Map::getTeam(std::string &name)
{
    for (auto &team : _teams) {
        if (team.name == name)
            return team;
    }

    throw Map::MapError("Team " + name + " not found");
}

void zappy::Map::addTeam(std::string &name)
{
    _teams.emplace_back(name);
}
