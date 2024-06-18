/*
** EPITECH PROJECT, 2024
** msz.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "command.h"

int command_msz(server_t *server, client_t *client)
{
    char *str;

    asprintf(&str, "msz %li %li\n", server->game->x, server->game->y);
    write(client->fd, str, strlen(str));
    free(str);
    return 1;
}
