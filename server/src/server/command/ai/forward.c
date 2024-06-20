/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward
*/

#include "server.h"

#include <stdio.h>

static void move_up(game_t *game, player_t *player)
{
    if (player->x == 0)
        player->x = game->x;
    player->x--;
}

static void move_down(game_t *game, player_t *player)
{
    if (player->x == game->x)
        player->x = 0;
    player->x++;
}

static void move_left(game_t *game, player_t *player)
{
    if (player->y == 0)
        player->y = game->y;
    player->y--;
}

static void move_right(game_t *game, player_t *player)
{
    if (player->y == game->y)
        player->y = 0;
    player->y++;
}

int forward_command(server_t *server, client_t *client)
{
    switch (client->player->direction) {
        case NORTH:
            move_up(server->game, client->player);
        case EAST:
            move_right(server->game, client->player);
        case SOUTH:
            move_down(server->game, client->player);
        case WEST:
            move_left(server->game, client->player);
    }
    dprintf(client->fd, "ok\n");
    return 1;
}
