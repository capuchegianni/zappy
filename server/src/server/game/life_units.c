/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** life_units
*/

#include "server.h"

#include <stdio.h>

bool death_event(client_t *client)
{
    if (client->player->inventory.food < 0) {
        dprintf(client->fd, "dead\n");
        reset_client(client);
        return true;
    }
    return false;
}

void update_life_units(server_t *server)
{
    time_t now = time(NULL);

    if (difftime(now, server->game->life_unit_update) <
    126.0 / server->game->frequence)
        return;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].is_playing) {
            server->clients[i].player->inventory.food--;
            death_event(&server->clients[i]);
        }
    }
    server->game->life_unit_update = now;
}
