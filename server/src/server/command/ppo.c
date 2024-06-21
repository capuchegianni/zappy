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

int internal_ppo(client_t *client, int fd)
{
    char *str;

    asprintf(&str, "ppo %li %li %li %u\n", client->player->id,
    client->player->x, client->player->y, client->player->direction);
    write(fd, str, strlen(str));
    free(str);
    return 1;
}

int command_ppo(server_t *server, client_t *client)
{
    if (!client->input->args[1]) {
        return write(client->fd, "sbp\n", 4);
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].player->id
        == (size_t) atoi(client->input->args[1])
        && !server->clients[i].is_graphic) {
            internal_ppo(&server->clients[i], client->fd);
            return 1;
        }
    }
    return write(client->fd, "sbp\n", 4);
}
