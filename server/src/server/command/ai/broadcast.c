/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "server.h"

#include <stdio.h>
#include <stdlib.h>

static size_t get_angle(size_t num1, size_t num2, size_t max)
{
    int val = num2 - num1;

    if ((size_t)abs(val) > max / 2 && val > 0)
        val -= max;
    if ((size_t)abs(val) > max / 2 && val < 0)
        val += max;
    return val;
}

static int get_orientation(int x, int y, player_t *broadcaster,
    player_t *receiver)
{
    if (receiver->x == broadcaster->x && receiver->y == broadcaster->y)
        return SAME;
    if (y > 0 && broadcaster->x == receiver->x)
        return CENTER_DOWN;
    if (y < 0 && broadcaster->x == receiver->x)
        return CENTER_UP;
    if (broadcaster->y == receiver->y && x > 0)
        return CENTER_LEFT;
    if (broadcaster->y == receiver->y && x < 0)
        return CENTER_RIGHT;
    if (y > 0 && x > 0)
        return DOWN_LEFT;
    if (y > 0 && x < 0)
        return DOWN_RIGHT;
    if (y < 0 && x > 0)
        return UP_LEFT;
    if (y < 0 && x < 0)
        return UP_RIGHT;
    return SAME;
}

static int get_sound_direction(server_t *server,
    player_t *broadcaster, player_t *receiver)
{
    size_t x = get_angle(broadcaster->x, receiver->x, server->game->x);
    size_t y = get_angle(broadcaster->y, receiver->y, server->game->y);
    orientation_t orientation = get_orientation(x, y, broadcaster, receiver);

    if (orientation == SAME)
        return orientation;
    if (receiver->direction == EAST)
        orientation += 2;
    if (receiver->direction == SOUTH)
        orientation += 4;
    if (receiver->direction == WEST)
        orientation += 6;
    if (orientation > 8)
        orientation -= 8;
    return orientation;
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
        tile = get_sound_direction(server, client->player, clients[i].player);
        send_message(client, &clients[i], tile);
    }
    dprintf(client->fd, "ok\n");
    return 1;
}
