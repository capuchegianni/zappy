/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#include "game.h"

#include <stdlib.h>

void init_items(items_t *items)
{
    items->food = 0;
    items->linemate = 0;
    items->deraumere = 0;
    items->sibur = 0;
    items->mendiane = 0;
    items->phiras = 0;
    items->thystame = 0;
}

bool init_map(game_t *game)
{
    game->map = malloc(sizeof(tile_t *) * game->x);
    if (!game->map)
        return false;
    for (size_t i = 0; i < game->x; i++) {
        game->map[i] = malloc(sizeof(tile_t) * game->y);
        if (!game->map[i])
            return false;
    }
    for (size_t i = 0; i < game->x; i++) {
        for (size_t j = 0; j < game->y; j++) {
            init_items(&game->map[i][j].items);
        }
    }
    return true;
}

void free_map(game_t *game)
{
    for (size_t i = 0; i < game->x; i++) {
        free(game->map[i]);
    }
    free(game->map);
}
