/*
** EPITECH PROJECT, 2024
** game_loop.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "command.h"
#include "game.h"

static void set_fds(fd_set *readfds, fd_set *writefds, server_t *server)
{
    FD_ZERO(readfds);
    FD_ZERO(writefds);
    FD_SET(server->fd, readfds);
    FD_SET(server->fd, writefds);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd > -1) {
            FD_SET(server->clients[i].fd, readfds);
            FD_SET(server->clients[i].fd, writefds);
        }
    }
}

static void send_infos(server_t *server, client_t *client, fd_set *writefds)
{
    if (!client->player->team_name || !client->is_graphic) {
        return;
    }
    if (client->fd > -1 && FD_ISSET(client->fd, writefds)) {
        command_mct(server, client);
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_playing
        && !server->clients[i].is_graphic) {
            internal_ppo(&server->clients[i], client->fd);
        }
    }
}

static void set_mct(server_t *server)
{
    fd_set writefds;
    fd_set readfds;
    struct timeval tv = {10, 10000};

    set_fds(&readfds, &writefds, server);
    if (select(FD_SETSIZE, &readfds, &writefds, NULL, &tv) > 0) {
        for (int i = 0; i < FD_SETSIZE; ++i) {
            send_infos(server, &server->clients[i], &writefds);
        }
    }
}

void spawn_ressource(server_t *server, float ressouce_density,
    int ressource_id)
{
    double max_food = (float)server->game->x *
        (float)server->game->y * (ressouce_density / 100.f);
    double current_food = 0;

    for (size_t i = 0; i < server->game->y; ++i) {
        for (size_t j = 0; j < server->game->x; ++j) {
            current_food +=
            (float)((&server->game->map[i][j].items.food)[ressource_id]);
        }
    }
    if (current_food < max_food || current_food == 0) {
        ((&server->game->map[rand() % server->game->y]
        [rand() % server->game->x].items.food)[ressource_id]) += 1;
    }
}

//TODO: Add tick base update
int update_game(server_t *server)
{
    set_mct(server);
    spawn_ressource(server, FOOD, 0);
    spawn_ressource(server, LINEMATE, 1);
    spawn_ressource(server, DERAUMERE, 2);
    spawn_ressource(server, SIBUR, 3);
    spawn_ressource(server, MENDIANE, 4);
    spawn_ressource(server, PHIRAS, 5);
    spawn_ressource(server, THYSTAME, 6);
    update_life_units(server);
    return 0;
}
