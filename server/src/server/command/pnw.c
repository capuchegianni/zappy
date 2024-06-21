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

    asprintf(&str, "pnw %li %li %li %li %li %s\n", 1, 0, 0, 1, 1, "test");
    write(client->fd, str, strlen(str));
    free(str);
    return 1;
}
