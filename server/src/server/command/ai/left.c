/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left
*/

#include "server.h"

#include <stdio.h>

int left_command(server_t *server, client_t *client)
{
    (void)server;
    if (client->player->direction == NORTH)
        client->player->direction = WEST;
    else
        client->player->direction--;
    dprintf(client->fd, "ok\n");
    return 1;
}
