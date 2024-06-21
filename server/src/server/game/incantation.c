/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include "server.h"

#include <stdio.h>

static void update_infos(game_t *game, client_t *clients, size_t i, size_t j)
{
    for (int k = 0; k < FD_SETSIZE; k++) {
        if (!clients[k].is_playing &&
        !clients[k].player->in_incantation)
            continue;
        if (clients[k].player->y != i && clients[k].player->x != j)
            continue;
        clients[k].player->in_incantation = false;
        game->map[i][j].incantation.occuring = false;
        game->map[i][j].incantation.start = 0;
        game->map[i][j].incantation.level = 0;
        dprintf(clients[k].fd, "Current level: %ld\n",
        clients[k].player->level);
    }
}

static void second_loop(game_t *game, client_t *clients, time_t *now, size_t i)
{
    for (size_t j = 0; j < game->x; j++) {
        if (!game->map[i][j].incantation.occuring)
            continue;
        if (difftime(*now, game->map[i][j].incantation.start) <
        300.0 / game->frequence)
            continue;
        update_infos(game, clients, i, j);
    }
}

void check_for_incantation(game_t *game, client_t *clients)
{
    time_t now = time(NULL);

    for (size_t i = 0; i < game->y; i++)
        second_loop(game, clients, &now, i);
}
