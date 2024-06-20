/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** utils
*/

#include "server.h"
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

void reset_client(client_t *client)
{
    client->is_playing = false;
    client->is_graphic = false;
    close(client->fd);
    client->fd = -1;
    init_items(&client->player->inventory);
    if (client->player->team_name) {
        free(client->player->team_name);
        client->player->team_name = NULL;
    }
}

void free_clients(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd > -1)
            close(server->clients[i].fd);
        if (server->clients[i].player->team_name)
            free(server->clients[i].player->team_name);
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
