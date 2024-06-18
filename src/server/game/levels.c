/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** levels
*/

#include "game.h"

static void level_two(game_t *game)
{
    game->levels[0].level = 2;
    game->levels[0].required_players = 1;
    init_items(&game->levels[0].required_items);
    game->levels[0].required_items.linemate = 1;
}

static void level_three(game_t *game)
{
    game->levels[1].level = 3;
    game->levels[1].required_players = 2;
    init_items(&game->levels[1].required_items);
    game->levels[1].required_items.linemate = 1;
    game->levels[1].required_items.deraumere = 1;
    game->levels[1].required_items.sibur = 1;
}

static void level_four(game_t *game)
{
    game->levels[2].level = 4;
    game->levels[2].required_players = 2;
    init_items(&game->levels[2].required_items);
    game->levels[2].required_items.linemate = 2;
    game->levels[2].required_items.sibur = 1;
    game->levels[2].required_items.phiras = 2;
}

static void level_five(game_t *game)
{
    game->levels[3].level = 5;
    game->levels[3].required_players = 4;
    init_items(&game->levels[3].required_items);
    game->levels[3].required_items.linemate = 1;
    game->levels[3].required_items.deraumere = 1;
    game->levels[3].required_items.sibur = 2;
    game->levels[3].required_items.phiras = 1;
}

static void level_six(game_t *game)
{
    game->levels[4].level = 6;
    game->levels[4].required_players = 4;
    init_items(&game->levels[4].required_items);
    game->levels[4].required_items.linemate = 1;
    game->levels[4].required_items.deraumere = 2;
    game->levels[4].required_items.sibur = 1;
    game->levels[4].required_items.mendiane = 3;
}

static void level_seven(game_t *game)
{
    game->levels[5].level = 7;
    game->levels[5].required_players = 6;
    init_items(&game->levels[5].required_items);
    game->levels[5].required_items.linemate = 1;
    game->levels[5].required_items.deraumere = 2;
    game->levels[5].required_items.sibur = 3;
    game->levels[5].required_items.phiras = 1;
}

static void level_eight(game_t *game)
{
    game->levels[6].level = 8;
    game->levels[6].required_players = 6;
    init_items(&game->levels[6].required_items);
    game->levels[6].required_items.linemate = 2;
    game->levels[6].required_items.deraumere = 2;
    game->levels[6].required_items.sibur = 2;
    game->levels[6].required_items.mendiane = 2;
    game->levels[6].required_items.phiras = 2;
    game->levels[6].required_items.thystame = 1;
}

void init_levels(game_t *game)
{
    level_two(game);
    level_three(game);
    level_four(game);
    level_five(game);
    level_six(game);
    level_seven(game);
    level_eight(game);
}
