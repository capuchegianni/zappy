/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** clients
*/

#include "server.h"
#include "misc.h"

#include <stdlib.h>
#include <stdio.h>

bool clients_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-c", 1, &args)) {
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->game->initial_team_size = atoi(args[0]);
    if (server->game->initial_team_size < 1) {
        printf("The initial client number must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}
