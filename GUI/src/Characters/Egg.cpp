/*
** EPITECH PROJECT, 2024
** Egg.cpp
** File description:
** zappy_gui
*/

#include "Egg.hpp"

zappy::Egg::Egg(std::size_t x, std::size_t y, std::size_t id, std::string team) : team(team), id(id), x(x), y(y) {}

zappy::Egg::~Egg() = default;
