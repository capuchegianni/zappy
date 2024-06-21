/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connect_nbr
*/

#include "server.h"

#include <stdio.h>
#include <string.h>

int connect_nbr_command(server_t *server, client_t *client)
{
    size_t i = 0;

    for (; i < server->game->teams_number; i++) {
        if (!strcmp(server->game->teams[i].name, client->player->team_name))
            break;
    }
    dprintf(client->fd, "%ld\n", server->game->teams[i].available_slots -
    server->game->teams[i].total_players_connected);
    return 1;
}
