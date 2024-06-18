/*
** EPITECH PROJECT, 2024
** bct.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "server_header.h"

int internal_bct(int x, int y, int fd)
{
    char *str;

    asprintf(&str, "bct %i %i %i %i %i %i %i %i %i\n", x, y,0,0,0,0,0,0,0);
    write(fd, str, strlen(str));
    free(str);

    return 1;
}

int command_bct(server_t *server, client_t *client)
{
    if (!client->input->args[1] || !client->input->args[2]) {
        return 0;
    }
    return internal_bct(atoi(client->input->args[1]), atoi(client->input->args[2]), client->fd);
}
