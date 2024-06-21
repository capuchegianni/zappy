/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** misc
*/

#pragma once

typedef struct player_s player_t;

typedef unsigned long size_t;

/**
 * @brief Free a char **
 * @param tab
*/
void free_tab(char **tab);

/**
 * @brief Get the lenght of a char **
 * @param tab
 * @return the size of the tab
*/
size_t tablen(char **tab);

/**
 * @brief Attribute an id to each newly created player
 * @param player
*/
void set_player_id(player_t *player);
