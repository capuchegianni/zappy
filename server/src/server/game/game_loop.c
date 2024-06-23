/*
** EPITECH PROJECT, 2024
** game_loop.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stddef.h>
#include <stdlib.h>

#include "server.h"
#include "command.h"
#include "game.h"
#include <sys/time.h>

void send_update_cell(int x, int y, server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].is_graphic) {
            internal_bct(x, y, server->clients[i].fd, server);
        }
    }
}

void spawn_ressource(server_t *server, float ressouce_density,
    int ressource_id)
{
    double max_food = (float)server->game->x *
        (float)server->game->y * (ressouce_density / 100.f);
    double current_food = 0;
    int y = rand() % server->game->y;
    int x = rand() % server->game->x;

    for (size_t i = 0; i < server->game->y; ++i) {
        for (size_t j = 0; j < server->game->x; ++j) {
            current_food +=
            (float)((&server->game->map[i][j].items.food)[ressource_id]);
        }
    }
    if (current_food < max_food || current_food == 0) {
        ((&server->game->map[y][x].items.food)[ressource_id]) += 1;
        send_update_cell(x, y, server);
    }
}

int update_game(server_t *server)
{
    is_a_team_winning(server);
    update_life_units(server);
    spawn_ressource(server, FOOD, 0);
    spawn_ressource(server, LINEMATE, 1);
    spawn_ressource(server, DERAUMERE, 2);
    spawn_ressource(server, SIBUR, 3);
    spawn_ressource(server, MENDIANE, 4);
    spawn_ressource(server, PHIRAS, 5);
    spawn_ressource(server, THYSTAME, 6);
    check_for_incantation(server->game, server->clients);
    return 0;
}
