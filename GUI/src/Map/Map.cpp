/*
** EPITECH PROJECT, 2024
** Map.cpp
** File description:
** zappy_gui
*/

#include "Map.hpp"

zappy::MapDrawables::MapDrawables()
{
    background.setFillColor(sf::Color::White);
}

zappy::MapDrawables::~MapDrawables() = default;

zappy::Map::Map(Assets &assets) : Map(10, 10, assets) {}

zappy::Map::Map(std::size_t width, std::size_t height, Assets &assets) : _assets(assets)
{
    _map.reserve(width);

    for (std::size_t i = 0; i < width; i++) {
        _map.emplace_back();

        _map.back().reserve(height);
        for (std::size_t j = 0; j < height; j++) {
            _map[i].emplace_back(i, j, _assets.font);
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

void zappy::Map::setDisplaySize(sf::Vector2f &size)
{
    _drawables.background.setSize(size);

    sf::Vector2f boxSize(size.x / _map.size(), size.y / _map[0].size());

    for (auto &row : _map) {
        for (auto &box : row) {
            sf::Vector2f position(box.x * boxSize.x + _drawables.background.getPosition().x, box.y * boxSize.y + _drawables.background.getPosition().y);

            box.setDisplaySize(boxSize);
            box.setDisplayPosition(position);
        }
    }

    for (auto &team : _teams) {
        for (auto &player : team.players) {
            sf::Vector2f position(player->x * boxSize.x + _drawables.background.getPosition().x, player->y * boxSize.y + _drawables.background.getPosition().y);

            player->setDisplaySize(boxSize);
            player->setDisplayPosition(position);
        }
    }
}

void zappy::Map::setDisplayPosition(sf::Vector2f &position)
{
    _drawables.background.setPosition(position);

    sf::Vector2f boxSize(_drawables.background.getSize().x / _map.size(), _drawables.background.getSize().y / _map[0].size());

    for (auto &row : _map) {
        for (auto &box : row) {
            sf::Vector2f position(box.x * boxSize.x + _drawables.background.getPosition().x, box.y * boxSize.y + _drawables.background.getPosition().y);

            box.setDisplaySize(boxSize);
            box.setDisplayPosition(position);
        }
    }

    for (auto &team : _teams) {
        for (auto &player : team.players) {
            sf::Vector2f position(player->x * boxSize.x + _drawables.background.getPosition().x, player->y * boxSize.y + _drawables.background.getPosition().y);

            player->setDisplaySize(boxSize);
            player->setDisplayPosition(position);
        }
    }
}

void zappy::Map::updateDisplay()
{
    sf::Vector2f position(_drawables.background.getPosition());
    sf::Vector2f size(_drawables.background.getSize());

    for (auto &row : _map) {
        for (auto &box : row) {
            box.updateText();
        }
    }

    setDisplayPosition(position);
    setDisplaySize(size);
}

void zappy::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_drawables.background, states);

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
