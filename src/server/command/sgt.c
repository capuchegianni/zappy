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
#include "server_header.h"

int command_sgt(server_t *server, client_t *client)
{
    char *str;

    asprintf(&str, "sgt %li\n", server->frequence);
    write(client->fd, str, strlen(str));
    free(str);
    return 1;
}
