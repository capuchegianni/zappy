/*
** EPITECH PROJECT, 2024
** SceneData.cpp
** File description:
** zappy_gui
*/

#include "SceneData.hpp"

zappy::SceneData::SceneData(zappy::Assets &assets)
{
    for (auto &tile : assets.tilesTextures) {
        tiles.push_back(std::make_shared<render3d::DisplayTile>(*tile));
    }
}

zappy::SceneData::~SceneData() = default;

std::shared_ptr<zappy::render3d::DisplayTile> &zappy::SceneData::getRandomTile()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tiles.size() - 1);

    return tiles[dis(gen)];
}
