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
    server->game->teams = calloc(tablen(args) + 1, sizeof(char *));
    for (; args[i]; i++)
        server->game->teams[i] = strdup(args[i]);
    server->game->teams[i] = NULL;
    free_tab(args);
    return true;
}
