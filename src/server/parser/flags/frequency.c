/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** frequency
*/

#include "server_header.h"

#include <stdlib.h>
#include <stdio.h>

bool frequency_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-f", 1, &args)) {
        server->game->frequence = 100;
        return true;
    }
    server->game->frequence = atoi(args[0]);
    if (server->game->frequence < 1) {
        printf("The frequence must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}
