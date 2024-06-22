/*
** EPITECH PROJECT, 2024
** SceneData.hpp
** File description:
** zappy_gui
*/

#pragma once

#include <random>

#include "Renderer/Camera.hpp"
#include "Renderer/DisplayTile.hpp"
#include "Assets.hpp"

namespace zappy
{
    class SceneData
    {
        public:
            SceneData(Assets &assets);
            ~SceneData();

            render3d::Camera camera;
            std::vector<std::shared_ptr<render3d::DisplayTile>> tiles;
            render3d::DisplayTile compassTile;

            std::shared_ptr<render3d::DisplayTile> &getRandomTile();
    };
}
