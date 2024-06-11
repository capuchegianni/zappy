/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#include "server_header.h"

#include <stdlib.h>
#include <stdio.h>

bool width_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-x", 1, &args)) {
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->width = atoi(args[0]);
    if (server->width < 1) {
        printf("The width must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}

bool height_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-y", 1, &args)) {
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->height = atoi(args[0]);
    if (server->height < 1) {
        printf("The height must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}
