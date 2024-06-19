/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** teams
*/

#include "server.h"
#include "misc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool team_already_exists(team_t *teams, char *team, size_t j)
{
    for (size_t i = 0; i < j; i++) {
        if (!strcmp(teams[i].name, team))
            return true;
    }
    return false;
}

static void loop(server_t *server, char **args)
{
    size_t i = 0;

    for (size_t j = 0; args[i]; i++) {
        if (team_already_exists(server->game->teams, args[i], j)) {
            server->game->teams_number--;
            continue;
        }
        server->game->teams[j].name = strdup(args[i]);
        server->game->teams[j].available_slots =
        server->game->initial_team_size;
        server->game->teams[j].total_players_connected = 0;
        j++;
    }
}

bool teams_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-n", -1, &args)) {
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->game->teams_number = tablen(args);
    server->game->teams = malloc(sizeof(team_t) * tablen(args));
    loop(server, args);
    free_tab(args);
    return true;
}
