/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include "server.h"

#include <stdio.h>

static void get_items(items_t *items, char **str)
{
    size_t food = items->food;
    size_t linemate = items->linemate;
    size_t deraumere = items->deraumere;
    size_t sibur = items->sibur;
    size_t mendiane = items->mendiane;
    size_t phiras = items->phiras;
    size_t thystame = items->thystame;

    asprintf(str, "food %ld, linemate %ld, deraumere %ld, sibur %ld, "
    "mendiane %ld, phiras %ld, thystame %ld", food, linemate,
    deraumere, sibur, mendiane, phiras, thystame);
}

int inventory_command(server_t *server, client_t *client)
{
    char *str = NULL;

    (void)server;
    get_items(&client->player->inventory, &str);
    dprintf(client->fd, "[ %s ]", str);
    return 1;
}
