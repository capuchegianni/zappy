/*
** EPITECH PROJECT, 2024
** sgt.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include "command.h"
#include <stdlib.h>

int command_sst(server_t *server, client_t *client)
{
    char *str;

    if (!client->input->args[1]) {
        return write(client->fd, "sbp\n", 4);
    }
    server->game->frequence = atoi(client->input->args[1]);
    asprintf(&str, "sst %li\n", server->game->frequence);
    write(client->fd, str, strlen(str));
    free(str);
    return 1;
}
