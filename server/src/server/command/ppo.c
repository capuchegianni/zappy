/*
** EPITECH PROJECT, 2024
** ppo.c
** File description:
** server
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "command.h"

int command_ppo(server_t *server, client_t *client)
{
    char *str;

    if (!client->input->args[1]) {
        write(client->fd, "sbp\n", 4);
        return 1;
    }

    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].player->id
        == (size_t) atoi(client->input->args[1])) {
            asprintf(&str, "ppo %li %li %li %u\n",
    server->clients[i].player->id,server->clients[i].player->x,
    server->clients[i].player->y, server->clients[i].player->direction);
            write(client->fd, str, strlen(str));
            free(str);
            return 1;
        }
    }
    write(client->fd, "sbp\n", 4);
    return 1;
}
