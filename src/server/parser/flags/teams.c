/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** teams
*/

#include "server_header.h"

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
    for (; args[i]; i++)
        server->game->teams[i].name = strdup(args[i]);
    free_tab(args);
    return true;
}
