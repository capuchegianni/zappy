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

static int others_items(server_t *server, client_t *client, const char *item)
{
    size_t x = client->player->x;
    size_t y = client->player->y;

    if (server->game->map[y][x].items.phiras && !strcmp(item, "phiras")) {
        server->game->map[y][x].items.phiras--;
        client->player->inventory.phiras++;
        return 1;
    }
    if (server->game->map[y][x].items.thystame && !strcmp(item, "thystame")) {
        server->game->map[y][x].items.thystame--;
        client->player->inventory.thystame++;
        return 1;
    }
    return 0;
}

static int other_items(server_t *server, client_t *client, const char *item)
{
    size_t x = client->player->x;
    size_t y = client->player->y;

    if (server->game->map[y][x].items.deraumere &&
    !strcmp(item, "deraumere")) {
        server->game->map[y][x].items.deraumere--;
        client->player->inventory.deraumere++;
        return 1;
    }
    if (server->game->map[y][x].items.sibur && !strcmp(item, "sibur")) {
        server->game->map[y][x].items.sibur--;
        client->player->inventory.sibur++;
        return 1;
    }
    if (server->game->map[y][x].items.mendiane && !strcmp(item, "mendiane")) {
        server->game->map[y][x].items.mendiane--;
        client->player->inventory.mendiane++;
        return 1;
    }
    return others_items(server, client, item);
}

static void pick_item(server_t *server, client_t *client, const char *item)
{
    size_t x = client->player->x;
    size_t y = client->player->y;
    int val = 0;

    if (server->game->map[y][x].items.food && !strcmp(item, "food")) {
        server->game->map[y][x].items.food--;
        client->player->inventory.food++;
        val = 1;
    }
    if (server->game->map[y][x].items.linemate && !strcmp(item, "linemate")) {
        server->game->map[y][x].items.linemate--;
        client->player->inventory.linemate++;
        val = 1;
    }
    if (!val)
        val = other_items(server, client, item);
    if (val)
        dprintf(client->fd, "ok\n");
    else
        dprintf(client->fd, "ko\n");
}

int take_command(server_t *server, client_t *client)
{
    if (!client->input[0].args[1]) {
        dprintf(client->fd, "ko\n");
        return 1;
    }
    for (int i = 0; objects[i]; i++) {
        if (!strcmp(objects[i], client->input[0].args[1])) {
            pick_item(server, client, client->input[0].args[1]);
            send_update_cell(client->player->x, client->player->y, server);
            return 1;
        }
    }
    dprintf(client->fd, "ko\n");
    return 1;
}
