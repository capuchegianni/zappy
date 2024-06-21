/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork
*/

#include "server.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fork_command(server_t *server, client_t *client)
{
    size_t i = 0;
    team_t *team = malloc(sizeof(team_t));

    for (; i < server->game->teams_number; i++) {
        if (!strcmp(server->game->teams[i].name, client->player->team_name))
            break;
    }
    team = &server->game->teams[i];
    team->available_slots++;
    srand(time(NULL));
    server->game->map[rand() % server->game->y]
    [rand() % server->game->x].egg_here++;
    dprintf(client->fd, "ok\n");
    return 1;
}
