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

static void set_mcts(server_t *server, client_t *client, fd_set *writefds)
{
    if (!client->player->team_name || !client->is_graphic) {
        return;
    }
    if (client->fd > -1 && FD_ISSET(client->fd, writefds)) {
        command_mct(server, client);
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
            set_mcts(server, &server->clients[i], &writefds);
        }
    }
}

int update_game(server_t *server)
{
    set_mct(server);
    server->game->map[rand() % server->game->x]
    [rand() % server->game->y].items.phiras += 1;
    return 0;
}
