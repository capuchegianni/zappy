/*
** EPITECH PROJECT, 2024
** Assets.cpp
** File description:
** zappy_gui
*/

#include "Assets.hpp"

zappy::Assets::Assets()
{
    if (!font.loadFromFile("../assets/fonts/LEMONMILK-Regular.otf"))
        throw Assets::AssetsError("Could not load font");

    if (!placeholderTexture.loadFromFile("../assets/textures/placeholder.png"))
        throw Assets::AssetsError("Could not load placeholder texture");
}

zappy::Assets::~Assets() = default;
