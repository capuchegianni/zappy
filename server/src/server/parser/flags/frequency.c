/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** frequency
*/

#include "server.h"
#include "misc.h"

#include <stdlib.h>
#include <stdio.h>

bool frequency_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-f", 1, &args)) {
        server->game->frequence = 100;
        return true;
    }
    if (atoi(args[0]) < 0) {
        printf("The frequence must be positive.\n");
        free_tab(args);
        return false;
    }
    server->game->frequence = atoi(args[0]);
    free_tab(args);
    return true;
}
