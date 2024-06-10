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

    if (!flag_parser(av, "-n", 1, &args)) {
        printf("Error on -n flag.\n");
        return false;
    }
    server->teams = calloc(tablen(args) + 1, sizeof(char *));
    for (; args[i]; i++)
        server->teams[i] = strdup(args[i]);
    server->teams[i] = NULL;
    free_tab(args);
    return true;
}
