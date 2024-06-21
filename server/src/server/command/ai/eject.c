/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include "server.h"

#include <stdio.h>

void eject_north(server_t *server, client_t *client, size_t y, size_t x)
{
    size_t yy = y == 0 ? server->game->y - 1 : y - 1;
    game_t *game = server->game;

    if (!game->map[y][x].player_here && !game->map[y][x].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[y][x].egg_here = 0;
    game->map[yy][x].player_here += game->map[y][x].player_here -1;
    game->map[y][x].player_here = 1;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == x &&
        server->clients[i].player->y == y &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->y = yy;
            dprintf(server->clients[i].fd, "eject: %d\n", SOUTH);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_east(server_t *server, client_t *client, size_t y, size_t x)
{
    size_t xx = x == server->game->x - 1 ? 0 : y + 1;
    game_t *game = server->game;

    if (!game->map[y][x].player_here && !game->map[y][x].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[y][x].egg_here = 0;
    game->map[y][xx].player_here += game->map[y][x].player_here -1;
    game->map[y][x].player_here = 1;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == x &&
        server->clients[i].player->y == y &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->x = xx;
            dprintf(server->clients[i].fd, "eject: %d\n", WEST);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_south(server_t *server, client_t *client, size_t y, size_t x)
{
    size_t yy = y == server->game->y - 1 ? 0 : y + 1;
    game_t *game = server->game;

    if (!game->map[y][x].player_here && !game->map[y][x].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[y][x].egg_here = 0;
    game->map[yy][x].player_here += game->map[y][x].player_here -1;
    game->map[y][x].player_here = 1;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == x &&
        server->clients[i].player->y == y &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->y = yy;
            dprintf(server->clients[i].fd, "eject: %d\n", NORTH);
        }
    }
    dprintf(client->fd, "ok\n");
}

void eject_west(server_t *server, client_t *client, size_t y, size_t x)
{
    size_t xx = x == 0 ? server->game->x - 1 : x - 1;
    game_t *game = server->game;

    if (game->map[y][x].player_here < 2 && !game->map[y][x].egg_here) {
        dprintf(client->fd, "ko\n");
        return;
    }
    game->map[y][x].egg_here = 0;
    game->map[y][xx].player_here += game->map[y][x].player_here -1;
    game->map[y][x].player_here = 1;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].player->x == x &&
        server->clients[i].player->y == y &&
        server->clients[i].player->id != client->player->id) {
            server->clients[i].player->x = xx;
            dprintf(server->clients[i].fd, "eject: %d\n", EAST);
        }
    }
    dprintf(client->fd, "ok\n");
}

int eject_command(server_t *server, client_t *client)
{
    switch (client->player->direction) {
        case NORTH:
            eject_north(server, client, client->player->y, client->player->x);
            break;
        case EAST:
            eject_east(server, client, client->player->y, client->player->x);
            break;
        case SOUTH:
            eject_south(server, client, client->player->y, client->player->x);
            break;
        case WEST:
            eject_west(server, client, client->player->y, client->player->x);
            break;
    }
    return 1;
}
