/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right
*/

#include "server.h"

#include <stdio.h>

int right_command(server_t *server, client_t *client)
{
    (void)server;
    if (client->player->direction == WEST)
        client->player->direction = NORTH;
    else
        client->player->direction++;
    dprintf(client->fd, "ok\n");
    return 1;
}
