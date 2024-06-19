/*
** EPITECH PROJECT, 2024
** tna.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "command.h"

int command_tna(server_t *server, client_t *client)
{
    char *str;

    for (size_t i = 0; i < server->game->teams_number; ++i) {
        asprintf(&str, "tna %s\n", server->game->teams[i].name);
        write(client->fd, str, strlen(str));
        free(str);
    }
    return 1;
}
