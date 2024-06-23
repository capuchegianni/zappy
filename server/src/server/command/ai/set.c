/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set
*/

#include "server.h"

#include <stdio.h>
#include <string.h>

static const char *objects[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
};


static void set_item(server_t *server, client_t *client, int objectID)
{
    size_t x = client->player->x;
    size_t y = client->player->y;

    if ((&client->player->inventory.food)[objectID]) {
        (&client->player->inventory.food)[objectID]--;
        (&server->game->map[y][x].items.food)[objectID]++;
        dprintf(client->fd, "ok\n");
    } else {
        dprintf(client->fd, "ko\n");
        return;
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_graphic) {
            dprintf(server->clients[i].fd, "pdr %li %i\n",
            client->player->id, objectID);
        }
    }
}

int set_command(server_t *server, client_t *client)
{
    if (!client->input[0].args[1]) {
        dprintf(client->fd, "ko\n");
        return 1;
    }
    for (int i = 0; objects[i]; i++) {
        if (!strcmp(objects[i], client->input[0].args[1])) {
            set_item(server, client, i);
            return 1;
        }
    }
    dprintf(client->fd, "ko\n");
    return 1;
}
