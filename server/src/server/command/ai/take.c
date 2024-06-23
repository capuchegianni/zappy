/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** take
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

static void pick_item(server_t *server, client_t *client, int objectID)
{
    size_t x = client->player->x;
    size_t y = client->player->y;

    if ((&server->game->map[y][x].items.food)[objectID]) {
        (&server->game->map[y][x].items.food)[objectID]--;
        (&client->player->inventory.food)[objectID]++;
    }
    dprintf(client->fd, "ok");
}

int take_command(server_t *server, client_t *client)
{
    if (!client->input[0].args[1]) {
        dprintf(client->fd, "ko\n");
        return 1;
    }

    for (int i = 0; objects[i]; i++) {
        if (!strcmp(objects[i], client->input[0].args[1])) {
            pick_item(server, client, i);
            send_update_cell(client->player->x, client->player->y, server);
            return 1;
        }
    }
    dprintf(client->fd, "ko\n");
    return 1;
}
