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

static int help(char **av)
{
    if (flag_parser(av, "--help", 0, NULL) || flag_parser(av, "-h", 0, NULL)) {
        printf("USAGE: ./zappy_server -p port -x width -y height "
        "-n name1 name2 ... -c clientsNb -f freq\n");
        return 1;
    }
    return 0;
}

void free_tab(char **tab)
{
    for (size_t i = 0; tab[i]; i++) {
        free(tab[i]);
    }
    free(tab);
}

size_t tablen(char **tab)
{
    size_t i = 0;

    for (; tab[i]; i++);
    return i;
}

int main(int ac, char **av)
{
    server_t *server = NULL;

    (void)ac;
    if (help(av))
        return 0;
    server = malloc(sizeof(server_t));
    if (!store_arguments_in_server(server, av)) {
        free(server);
        return 84;
    }
    return fserver(server);
}
