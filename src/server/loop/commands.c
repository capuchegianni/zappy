/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** commands
*/

#include "server_header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int add_buffer(client_t *client, char *buffer)
{
    if (client->append_mode) {
        client->input->body_len += strlen(buffer);
        client->input->body = realloc(client->input->body,
        client->input->body_len + 1);
        if (client->input->body == NULL)
            return 84;
        client->input->body = strcat(client->input->body, buffer);
    } else {
        client->input->body = realloc(client->input->body, strlen(buffer) + 1);
        if (client->input->body == NULL)
            return 84;
        client->input->body = strcpy(client->input->body, buffer);
        client->input->body_len = strlen(client->input->body);
    }
    return 0;
}

static int get_command(client_t *client, char *buffer)
{
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = 0;
        if (buffer[strlen(buffer) - 1] == '\r') {
            buffer[strlen(buffer) - 1] = 0;
            client->append_mode = false;
        } else
            client->append_mode = true;
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
    read_val = read(client->fd, buffer, LEN);
    if (read_val <= 0) {
        printf("Client disconnected\n");
        reset_client(server, client);
        return 0;
    }
    if (get_command(client, buffer))
        return 84;
    return 0;
}
