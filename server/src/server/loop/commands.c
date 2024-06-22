/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** commands
*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int add_buffer(client_t *client, char *buffer)
{
    int i = 0;

    for (; client->input[i].body; i++);
    if (i == 10)
        return 0;
    client->input[i].body = strdup(buffer);
    if (client->input[i].body == NULL)
        return 84;
    client->input[i].body_len = strlen(client->input[i].body);
    return 0;
}

static int get_command(client_t *client, char *buffer)
{
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
        if (buffer[strlen(buffer) - 1] == '\r')
            buffer[strlen(buffer) - 1] = 0;
    }
    if (add_buffer(client, buffer))
        return 84;
    return 0;
}

int init_read_buffer(server_t *server, client_t *client)
{
    char buffer[LEN];
    int read_val = 0;

    memset(buffer, 0, LEN);
    read_val = read(client->fd, buffer, LEN - 1);
    if (read_val <= 0) {
        printf("Client disconnected\n");
        reset_client(server, client);
        return 0;
    }
    if (get_command(client, buffer))
        return 84;
    return 0;
}
