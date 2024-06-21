/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include "server.h"

#include <stdio.h>

void eject_north(server_t *server, client_t *client, size_t pos[2])
{
    size_t y = pos[0] == 0 ? server->game->y : pos[0] - 1;
    game_t *game = server->game;

    if (!game->map[pos[0]][pos[1]].player_here &&
    !game->map[pos[0]][pos[1]].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[pos[0]][pos[1]].egg_here = 0;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == pos[1] &&
        server->clients[i].player->y == pos[0] &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->y = y;
            dprintf(server->clients[i].fd, "eject: %d\n", SOUTH);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_east(server_t *server, client_t *client, size_t pos[2])
{
    size_t x = pos[1] == server->game->x ? 0 : pos[0] + 1;
    game_t *game = server->game;

    if (!game->map[pos[0]][pos[1]].player_here &&
    !game->map[pos[0]][pos[1]].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[pos[0]][pos[1]].egg_here = 0;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == pos[1] &&
        server->clients[i].player->y == pos[0] &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->x = x;
            dprintf(server->clients[i].fd, "eject: %d\n", WEST);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_south(server_t *server, client_t *client, size_t pos[2])
{
    size_t y = pos[0] == server->game->y ? 0 : pos[0] + 1;
    game_t *game = server->game;

    if (!game->map[pos[0]][pos[1]].player_here &&
    !game->map[pos[0]][pos[1]].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[pos[0]][pos[1]].egg_here = 0;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == pos[1] &&
        server->clients[i].player->y == pos[0] &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->y = y;
            dprintf(server->clients[i].fd, "eject: %d\n", NORTH);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_west(server_t *server, client_t *client, size_t pos[2])
{
    size_t x = pos[1] == 0 ? server->game->x : pos[0] - 1;
    game_t *game = server->game;

    if (!game->map[pos[0]][pos[1]].player_here &&
    !game->map[pos[0]][pos[1]].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[pos[0]][pos[1]].egg_here = 0;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == pos[1] &&
        server->clients[i].player->y == pos[0] &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->x = x;
            dprintf(server->clients[i].fd, "eject: %d\n", EAST);
        }
    }
    dprintf(client->fd, "ok\n");
}

int eject_command(server_t *server, client_t *client)
{
    size_t pos[2] = {client->player->y, client->player->x};

    switch (client->player->direction) {
        case NORTH:
            eject_north(server, client, pos);
            break;
        case EAST:
            eject_east(server, client, pos);
            break;
        case SOUTH:
            eject_south(server, client, pos);
            break;
        case WEST:
            eject_west(server, client, pos);
            break;
    }
    return 1;
}
