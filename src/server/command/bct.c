/*
** EPITECH PROJECT, 2024
** bct.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

int internal_bct(int x, int y, int fd, server_t *server)
{
    char *str;
    tile_t tile = server->game->map[x][y];

    asprintf(&str, "bct %i %i %zu %zu %zu %zu %zu %zu %zu\n", x, y,
        tile.items.food, tile.items.linemate, tile.items.deraumere,
        tile.items.sibur, tile.items.mendiane, tile.items.phiras,
        tile.items.thystame);
    write(fd, str, strlen(str));
    free(str);
    return 1;
}

int command_bct(server_t *server, client_t *client)
{
    if (!client->input->args[1] || !client->input->args[2]) {
        write(client->fd, "sbp\n", 4);
        return 1;
    }
    return internal_bct(atoi(client->input->args[1]),
    atoi(client->input->args[2]), client->fd, server);
}
