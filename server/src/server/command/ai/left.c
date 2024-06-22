/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left
*/

#include "server.h"
#include "command.h"

#include <stdio.h>

int left_command(server_t *server, client_t *client)
{
    (void)server;
    if (client->player->direction == NORTH)
        client->player->direction = WEST;
    else
        client->player->direction--;
    if (client->player->direction == 5)
        client->player->direction = 1;
    if (client->player->direction == 0)
        client->player->direction = 5;
    dprintf(client->fd, "ok\n");
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_graphic) {
            internal_ppo(client, server->clients[i].fd);
        }
    }
    return 1;
}
