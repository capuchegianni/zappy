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

static void add_eggs(game_t *game)
{
    srand(time(NULL));
    for (size_t i = 0; i < game->teams_number; i++)
        for (size_t j = 0; j < game->initial_team_size; j++)
            game->map[rand() % game->y][rand() % game->x].egg_here++;
}

bool init_map(game_t *game)
{
    game->map = malloc(sizeof(tile_t *) * game->y);
    if (!game->map)
        return false;
    for (size_t i = 0; i < game->y; i++) {
        game->map[i] = malloc(sizeof(tile_t) * game->x);
        if (!game->map[i])
            return false;
        for (size_t j = 0; j < game->x; j++) {
            init_items(&game->map[i][j].items);
            game->map[i][j].player_here = false;
            game->map[i][j].egg_here = false;
        }
    }
    add_eggs(game);
    return true;
}

void free_map(game_t *game)
{
    for (size_t i = 0; i < game->y; i++) {
        free(game->map[i]);
    }
    free(game->map);
}
