/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** main
*/

#include "server_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

static int help(void)
{
    printf("USAGE: ./zappy_server port\n");
    printf("\tport  is the port number on which the server socket listens\n");
    return 0;
}

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));

    if (ac != 2) {
        free(server);
        printf("Invalid number of arguments\n");
        return 84;
    }
    if (strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0) {
        free(server);
        return help();
    }
    if (error_management(atoi(av[1])) == 84) {
        free(server);
        return 84;
    }
    return fserver(av, server);
}
