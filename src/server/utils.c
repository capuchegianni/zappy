/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** utils
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

char **s_to_t(char *str)
{
    char **tab = calloc(2, sizeof(char *));

    tab[0] = strdup(str);
    return tab;
}

void reset_client(client_t *client)
{
    client->is_playing = false;
    close(client->fd);
    client->fd = -1;
    init_items(&client->player->inventory);
    free(client->input->args);
    client->input->args = calloc(1, sizeof(char *));
    client->input->body = NULL;
}

void free_clients(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        free(server->clients[i].input->args);
        if (server->clients[i].input->body)
            free(server->clients[i].input->body);
        free(server->clients[i].input);
        if (server->clients[i].fd > -1)
            close(server->clients[i].fd);
        free(server->clients[i].player);
    }
    free(server->clients);
    for (size_t i = 0; i < server->game->teams_number; i++)
        free(server->game->teams[i].name);
    free(server->game->teams);
    free_map(server->game);
    free(server->game);
    free(server);
}

int error_management(int port)
{
    if (port < 1024 || port > 65535) {
        printf("Invalid specified port\n");
        return 84;
    }
    return 0;
}
