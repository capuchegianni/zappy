/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** win_condition
*/

#include "server.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char **teams_above_six_players(server_t *server)
{
    char **teams = calloc(sizeof(char *), server->game->teams_number + 1);
    size_t j = 0;

    for (size_t i = 0; i < server->game->teams_number; i++) {
        if (server->game->teams[i].total_players_connected < 6)
            continue;
        teams[j] = strdup(server->game->teams[i].name);
        j++;
    }
    return teams;
}

static bool has_won(size_t players, client_t *clients, char *team)
{
    if (players < 6)
        return false;
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (clients[i].fd > -1 && clients[i].is_graphic) {
            dprintf(clients[i].fd, "seg %s\n", team);
            return true;
        }
    }
    return false;
}

static size_t increase_player_number(client_t *cli, char *team)
{
    size_t player = 0;

    for (int i = 0; i < FD_SETSIZE; i++) {
        if (!cli[i].is_playing && cli[i].is_graphic)
            continue;
        if (strcmp(cli[i].player[i].team_name, team))
            continue;
        if (cli[i].player->level == 8)
            player++;
    }
    return player;
}

void is_a_team_winning(server_t *server)
{
    char **teams = teams_above_six_players(server);
    client_t *clients = server->clients;
    size_t players_at_max_level = 0;

    if (!teams)
        return;
    for (size_t j = 0; teams[j]; j++) {
        players_at_max_level = increase_player_number(clients, teams[j]);
        if (has_won(players_at_max_level, clients, teams[j])) {
            server->game->frequence = 0;
            server->game->end = true;
            break;
        }
    }
}
