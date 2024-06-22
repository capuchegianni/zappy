/*
** EPITECH PROJECT, 2024
** plv.c
** File description:
** server
*/

#include "command.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int internal_plv(client_t *client, int fd)
{
    char *str;

    asprintf(&str, "plv %li %li\n", client->player->id, client->player->level);
    write(fd, str, strlen(str));
    free(str);
    return 1;
}

int command_plv(server_t *server, client_t *client)
{
    if (!client->input->args[1]) {
        return write(client->fd, "sbp\n", 4);
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].player->id
        == (size_t) atoi(client->input->args[1])
            && !server->clients[i].is_graphic) {
            internal_plv(&server->clients[i], client->fd);
            return 1;
        }
    }
    return write(client->fd, "sbp\n", 4);
}
