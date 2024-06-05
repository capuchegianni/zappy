/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** GUI
*/

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Map/Map.hpp"
#include "Display/EventLogger.hpp"
#include "Display/Renderer/Camera.hpp"
#include "Display/Renderer/Tile.hpp"

int main(int ac, char **av)
{
    zappy::Assets assets;
    zappy::render3d::Camera camera;
    zappy::render3d::Tile tile(assets);

}
