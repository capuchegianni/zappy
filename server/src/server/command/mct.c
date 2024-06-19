/*
** EPITECH PROJECT, 2024
** mct.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <unistd.h>
#include "command.h"

int command_mct(server_t *server, client_t *client)
{
    int ret = 1;

    for (size_t i = 0; i < server->game->x; ++i) {
        for (size_t j = 0; j < server->game->y; ++j) {
            ret &= internal_bct(i, j, client->fd, server);
        }
    }
    return ret;
}
