/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "server.h"

#include <stdio.h>
#include <math.h>

static int get_angle(size_t dy, size_t dx)
{
    double angle = atan2(dy, dx) * (180 / 3.14159265);

    if (-22.5 <= angle && angle < 22.5)
        return 1;
    if (22.5 <= angle && angle < 67.5)
        return 2;
    if (67.5 <= angle && angle < 112.5)
        return 3;
    if (112.5 <= angle && angle < 157.5)
        return 4;
    if (157.5 <= angle || angle < -157.5)
        return 5;
    if (-157.5 <= angle && angle < -112.5)
        return 6;
    if (-112.5 <= angle && angle < -67.5)
        return 7;
    if (-67.5 <= angle && angle < -22.5)
        return 8;
    return -1;
}

static int get_orientation(server_t *server,
    player_t *broadcaster, player_t *receiver)
{
    size_t dy = receiver->y - broadcaster->y;
    size_t dx = receiver->x - broadcaster->x;

    if (dx > server->game->x / 2)
        dx -= server->game->x;
    else
        dx += server->game->x;
    if (dy > server->game->y / 2)
        dy -= server->game->y;
    else
        dy += server->game->y;
    if (dx == 0 && dy == 0)
        return 0;
    return get_angle(dy, dx);
}

static void send_message(client_t *broadcaster, client_t *receiver, int tile)
{
    dprintf(receiver->fd, "message %d, %s\n", tile,
    broadcaster->input[0].args[1]);
}

static void send_to_graphic(server_t *server, client_t *client)
{
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_graphic) {
            dprintf(server->clients[i].fd, "pbc %ld %s\n", client->player->id,
            client->input[0].args[1]);
            break;
        }
    }
}

int broadcast_command(server_t *server, client_t *client)
{
    client_t *clients = server->clients;
    int tile = 0;

    if (!client->input[0].args[1]) {
        dprintf(client->fd, "ko\n");
        return 1;
    }
    send_to_graphic(server, client);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (!clients[i].is_playing || clients[i].is_graphic)
            continue;
        if (clients[i].player->id == client->player->id)
            continue;
        tile = get_orientation(server, client->player, clients[i].player);
        send_message(client, &clients[i], tile);
    }
    dprintf(client->fd, "ok\n");
    return 1;
}
