/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward
*/

#include "server.h"
#include "command.h"

#include <stdio.h>

static void move_up(game_t *game, player_t *player)
{
    if (player->y == 0)
        player->y = game->y - 1;
    else
        player->y--;
}

static void move_down(game_t *game, player_t *player)
{
    if (player->y == game->y - 1)
        player->y = 0;
    else
        player->y++;
}

static void move_left(game_t *game, player_t *player)
{
    if (player->x == 0)
        player->x = game->x - 1;
    else
        player->x--;
}

static void move_right(game_t *game, player_t *player)
{
    if (player->x == game->x - 1)
        player->x = 0;
    else
        player->x++;
}

static void select_move(server_t *server, client_t *client)
{
    switch (client->player->direction) {
        case NORTH:
            move_up(server->game, client->player);
            break;
        case EAST:
            move_right(server->game, client->player);
            break;
        case SOUTH:
            move_down(server->game, client->player);
            break;
        case WEST:
            move_left(server->game, client->player);
            break;
    }
}

int forward_command(server_t *server, client_t *client)
{
    server->game->map[client->player->y][client->player->x].player_here--;
    select_move(server, client);
    server->game->map[client->player->y][client->player->x].player_here++;
    dprintf(client->fd, "ok\n");
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (client->fd > -1 && server->clients[i].is_graphic) {
            internal_ppo(client, server->clients[i].fd);
        }
    }
    return 1;
}
