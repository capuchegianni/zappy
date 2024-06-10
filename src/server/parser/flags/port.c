/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** port
*/

#include "server_header.h"

#include <stdlib.h>
#include <stdio.h>

bool port_flag(server_t *server, char **av)
{
    char **args = NULL;

    if (!flag_parser(av, "-p", 1, &args)) {
        printf("Error on -p flag.\n");
        return false;
    }
    if (atoi(args[0]) < 1024 || atoi(args[0]) > 65535) {
        printf("Invalid specified port.\n");
        free_tab(args);
        return false;
    }
    server->port = atoi(args[0]);
    free_tab(args);
    return true;
}
