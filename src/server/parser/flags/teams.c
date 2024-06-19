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

bool teams_flag(server_t *server, char **av)
{
    char **args = NULL;
    size_t i = 0;

    if (!flag_parser(av, "-n", -1, &args)) {
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->game->teams_number = tablen(args);
    server->game->teams = malloc(sizeof(team_t) * tablen(args));
    for (; args[i]; i++) {
        server->game->teams[i].name = strdup(args[i]);
        server->game->teams[i].available_slots =
        server->game->initial_team_size;
        server->game->teams[i].total_players_connected = 0;
    }
    free_tab(args);
    return true;
}
