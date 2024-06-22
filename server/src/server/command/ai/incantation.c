/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include "server.h"

#include <stdio.h>

static void remove_items(items_t *items, const level_t *level)
{
    items->linemate -= level->required_items.linemate;
    items->deraumere -= level->required_items.deraumere;
    items->sibur -= level->required_items.sibur;
    items->mendiane -= level->required_items.mendiane;
    items->phiras -= level->required_items.phiras;
    items->linemate -= level->required_items.linemate;
}

static bool check_items(server_t *server, const level_t *level, size_t p[2],
    player_t *player)
{
    game_t *game = server->game;

    if (player->inventory.food < 10)
        return false;
    if (game->map[p[0]][p[1]].items.linemate < level->required_items.linemate)
        return false;
    if (game->map[p[0]][p[1]].items.deraumere <
    level->required_items.deraumere)
        return false;
    if (game->map[p[0]][p[1]].items.sibur < level->required_items.sibur)
        return false;
    if (game->map[p[0]][p[1]].items.mendiane < level->required_items.mendiane)
        return false;
    if (game->map[p[0]][p[1]].items.phiras < level->required_items.phiras)
        return false;
    if (game->map[p[0]][p[1]].items.thystame < level->required_items.thystame)
        return false;
    return true;
}

static bool check_players_level(server_t *server, const level_t *level,
    size_t y, size_t x)
{
    size_t players = 0;

    for (int i = 0; i < FD_SETSIZE; i++) {
        if (!server->clients[i].is_playing)
            continue;
        if (server->clients[i].player->y != y &&
        server->clients[i].player->x != x)
            continue;
        if (server->clients[i].player->level != level->level - 1)
            continue;
        players++;
    }
    if (players < level->required_players)
        return false;
    return true;
}

static void start_incantation(server_t *server, const level_t *level, size_t y,
    size_t x)
{
    remove_items(&server->game->map[y][x].items, level);
    server->game->map[y][x].incantation.level = level->level;
    server->game->map[y][x].incantation.occuring = true;
    server->game->map[y][x].incantation.start = time(NULL);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (!server->clients[i].is_playing)
            continue;
        if (server->clients[i].player->y != y &&
        server->clients[i].player->x != x)
            continue;
        if (server->clients[i].player->level != level->level - 1)
            continue;
        server->clients[i].player->in_incantation = true;
        server->clients[i].player->level++;
        dprintf(server->clients[i].fd, "Elevation underway\n");
    }
    return;
}

int incantation_command(server_t *server, client_t *client)
{
    const level_t next_level = server->game->levels[client->player->level];
    size_t y = client->player->y;
    size_t x = client->player->x;
    tile_t tile = server->game->map[y][x];

    if (tile.player_here < next_level.required_players ||
    !check_players_level(server, &next_level, y, x)) {
        dprintf(client->fd, "ko\n");
        client->input[1].exec_time = 0;
        return 1;
    }
    if (!check_items(server, &next_level, (size_t[2]){y, x}, client->player)) {
        dprintf(client->fd, "ko\n");
        client->input[1].exec_time = 0;
        return 1;
    }
    start_incantation(server, &next_level, y, x);
    return 1;
}
