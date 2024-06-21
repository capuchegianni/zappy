/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static tile_t get_tile_content(server_t *server, int y, int x)
{
    tile_t tile;

    x = (x + server->game->x) % server->game->x;
    y = (y + server->game->y) % server->game->y;
    tile = server->game->map[y][x];
    return tile;
}

static void get_items(tile_t *tile, char **str)
{
    char *player = tile->player_here ? " player" : "";
    char *egg = tile->egg_here ? " egg" : "";
    char *food = tile->items.food ? " food" : "";
    char *linemate = tile->items.linemate ? " linemate" : "";
    char *deraumere = tile->items.deraumere ? " deraumere" : "";
    char *sibur = tile->items.sibur ? " sibur" : "";
    char *mendiane = tile->items.mendiane ? " mendiane" : "";
    char *phiras = tile->items.phiras ? " phiras" : "";
    char *thystame = tile->items.thystame ? " thystame" : "";

    asprintf(str, "%s%s%s%s%s%s%s%s%s", player, egg, food, linemate,
    deraumere, sibur, mendiane, phiras, thystame);
}

static void look_north(server_t *server, client_t *client,
    level_t *current_level, size_t pos[2])
{
    char *str = NULL;
    char *str2 = NULL;
    char *temp = NULL;
    tile_t tile;

    for (int i = 0; i <= (int)current_level->level; i++) {
        for (int j = -i; j <= i; j++) {
            temp = str ? str : strdup("");
            tile = get_tile_content(server, pos[0] - i, pos[1] + j);
            get_items(&tile, &str2);
            asprintf(&str, "%s%s%s", temp,
            (i == 0 && j == -i) ? "" : ",", str2);
            free(temp);
            free(str2);
        }
    }
    dprintf(client->fd, "[%s ]\n", str);
    free(str);
}

static void look_east(server_t *server, client_t *client,
    level_t *current_level, size_t pos[2])
{
    char *str = NULL;
    char *str2 = NULL;
    char *temp = NULL;
    tile_t tile;

    for (int i = 0; i <= (int)current_level->level; i++) {
        for (int j = -i; j <= i; j++) {
            temp = str ? str : strdup("");
            tile = get_tile_content(server, pos[0] + j, pos[1] + i);
            get_items(&tile, &str2);
            asprintf(&str, "%s%s%s", temp,
            (i == 0 && j == -i) ? "" : ",", str2);
            free(temp);
            free(str2);
        }
    }
    dprintf(client->fd, "[%s ]\n", str);
    free(str);
}

static void look_south(server_t *server, client_t *client,
    level_t *current_level, size_t pos[2])
{
    char *str = NULL;
    char *str2 = NULL;
    char *temp = NULL;
    tile_t tile;

    for (int i = 0; i <= (int)current_level->level; i++) {
        for (int j = -i; j <= i; j++) {
            temp = str ? str : strdup("");
            tile = get_tile_content(server, pos[0] + i, pos[1] - j);
            get_items(&tile, &str2);
            asprintf(&str, "%s%s%s", temp,
            (i == 0 && j == -i) ? "" : ",", str2);
            free(temp);
            free(str2);
        }
    }
    dprintf(client->fd, "[%s ]\n", str);
    free(str);
}

static void look_west(server_t *server, client_t *client,
    level_t *current_level, size_t pos[2])
{
    char *str = NULL;
    char *str2 = NULL;
    char *temp = NULL;
    tile_t tile;

    for (int i = 0; i <= (int)current_level->level; i++) {
        for (int j = -i; j <= i; j++) {
            temp = str ? str : strdup("");
            tile = get_tile_content(server, pos[0] - j, pos[1] - i);
            get_items(&tile, &str2);
            asprintf(&str, "%s%s%s", temp,
            (i == 0 && j == -i) ? "" : ",", str2);
            free(temp);
            free(str2);
        }
    }
    dprintf(client->fd, "[%s ]\n", str);
    free(str);
}

int look_command(server_t *server, client_t *client)
{
    size_t pos[2] = {client->player->y, client->player->x};
    level_t current_level = server->game->levels[client->player->level - 1];

    switch (client->player->direction) {
        case NORTH:
            look_north(server, client, &current_level, pos);
            break;
        case EAST:
            look_east(server, client, &current_level, pos);
            break;
        case SOUTH:
            look_south(server, client, &current_level, pos);
            break;
        case WEST:
            look_west(server, client, &current_level, pos);
            break;
    }
    return 1;
}
