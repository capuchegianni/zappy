/*
** EPITECH PROJECT, 2024
** Team.cpp
** File description:
** zappy_gui
*/

#include "Team.hpp"

zappy::Team::Team(std::string &name) : name(name)
{
    color = generateColor(name);
}

zappy::Team::~Team()
{
}

void zappy::Team::addPlayer(const std::shared_ptr<Trantorien> &player)
{
    players.push_back(player);
}

void zappy::Team::removePlayerById(std::size_t id)
{
    for (auto it = players.begin(); it != players.end(); it++) {
        if ((*it)->id == id) {
            players.erase(it);
            return;
        }
    }

    throw Team::TeamError("Player " + std::to_string(id) + " not found");
}

std::shared_ptr<zappy::Trantorien> zappy::Team::getPlayerById(std::size_t id)
{
    for (auto &player : players) {
        if (player->id == id)
            return player;
    }

    throw Team::TeamError("Player " + std::to_string(id) + " not found");
}

std::size_t zappy::Team::getPlayerIndexById(std::size_t id)
{
    for (std::size_t i = 0; i < players.size(); i++) {
        if (players[i]->id == id)
            return i;
    }

    throw Team::TeamError("Player not found");
}

void zappy::Team::addEgg(const std::shared_ptr<Egg> &egg)
{
    eggs.push_back(egg);
}

void zappy::Team::removeEggById(std::size_t id)
{
    for (auto it = eggs.begin(); it != eggs.end(); it++) {
        if ((*it)->id == id) {
            eggs.erase(it);
            return;
        }
    }

    throw Team::TeamError("Egg " + std::to_string(id) + " not found");
}

sf::Color zappy::Team::generateColor(const std::string &name)
{
    std::seed_seq seed(name.begin(), name.end());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 255);

    int red = distribution(generator);
    int green = distribution(generator);
    int blue = distribution(generator);

    return sf::Color(red, green, blue);
}
