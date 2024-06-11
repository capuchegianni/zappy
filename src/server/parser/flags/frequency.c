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
        printf("%s%s", HELP, HELP2);
        return false;
    }
    server->frequence = atoi(args[0]);
    if (server->frequence < 1) {
        printf("The frequence must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}
