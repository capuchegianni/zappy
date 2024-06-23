/*
** EPITECH PROJECT, 2024
** plv.c
** File description:
** server
*/

#include "server.h"
#include "command.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static void get_items(items_t *items, char **str)
{
    size_t food = items->food;
    size_t linemate = items->linemate;
    size_t deraumere = items->deraumere;
    size_t sibur = items->sibur;
    size_t mendiane = items->mendiane;
    size_t phiras = items->phiras;
    size_t thystame = items->thystame;

    asprintf(str, "%ld %ld %ld %ld %ld %ld %ld", food, linemate,
    deraumere, sibur, mendiane, phiras, thystame);
}

int internal_pin(client_t *client, int fd)
{
    char *str;

    get_items(&client->player->inventory, &str);
    dprintf(fd, "pin %li %li %li %s", client->player->id, client->player->x,
    client->player->y, str);
    free(str);
    return 1;
}

int command_pin(server_t *server, client_t *client)
{
    if (!client->input->args[1]) {
        return write(client->fd, "sbp\n", 4);
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].player->id
        == (size_t) atoi(client->input->args[1])
            && !server->clients[i].is_graphic) {
            internal_pin(&server->clients[i], client->fd);
            return 1;
        }
    }
    return write(client->fd, "sbp\n", 4);
}
