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
#include <unistd.h>

int internal_pfk(client_t *client, int fd)
{
    char *str;

    asprintf(&str, "pfk %li\n", client->player->id);
    write(fd, str, strlen(str));
    free(str);
    return 1;
}

int fork_command(server_t *server, client_t *client)
{
    size_t i = 0;
    team_t *teams = server->game->teams;

    for (; i < server->game->teams_number; i++) {
        if (!strcmp(server->game->teams[i].name, client->player->team_name))
            break;
    }
    teams[i].available_slots++;
    srand(time(NULL));
    server->game->map[rand() % server->game->y]
    [rand() % server->game->x].egg_here++;
    dprintf(client->fd, "ok\n");

    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_graphic) {
            internal_pfk(client, server->clients[i].fd);
        }
    }

    return 1;
}
