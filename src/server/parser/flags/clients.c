/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** clients
*/

#include "server_header.h"

#include <stdlib.h>
#include <stdio.h>

bool clients_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-c", 1, &args)) {
        printf("Error with -c flag.\n");
        return false;
    }
    server->initial_client_number = atoi(args[0]);
    if (server->initial_client_number < 1) {
        printf("The initial client number must be higher than 0.\n");
        free_tab(args);
        return false;
    }
    free_tab(args);
    return true;
}
