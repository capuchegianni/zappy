/*
** EPITECH PROJECT, 2024
** pnw.c
** File description:
** server
*/

#include "command.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int command_pnw(server_t *server, client_t *client)
{
    char *str;

    asprintf(&str, "pnw %li %li %li %u %zu %s\n", client->player->id,
    client->player->x, client->player->y, client->player->direction,
    client->player->level, client->player->team_name);
    write(client->fd, str, strlen(str));
    free(str);
    return 1;
}
