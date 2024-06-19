/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** argument_parser
*/

#include "server.h"
#include "misc.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t flag_exists(char *flag, char **av)
{
    for (int i = 1; av[i]; i++) {
        if (strcmp(flag, av[i]) == 0)
            return i;
    }
    return -1;
}

static char **get_arguments(char **av, int flag_index, size_t args_number)
{
    char **args = calloc(args_number + 1, sizeof(char *));
    size_t j = 0;

    for (size_t i = flag_index + 1; av[i] && j < args_number; i++) {
        if (av[i][0] == '-') {
            free_tab(args);
            return NULL;
        }
        args[j] = strdup(av[i]);
        j++;
    }
    args[j] = NULL;
    if (!j) {
        free_tab(args);
        return NULL;
    }
    return args;
}

static char **get_arguments_with_no_limit(char **av, int flag_index)
{
    char **args = calloc(1, sizeof(char *));
    size_t j = 0;

    for (size_t i = flag_index + 1; av[i] && av[i][0] != '-'; i++) {
        args[j] = strdup(av[i]);
        j++;
        args = realloc(args, sizeof(char *) * (j + 1));
    }
    if (!j) {
        free_tab(args);
        return NULL;
    }
    args[j] = NULL;
    return args;
}

bool flag_parser(char **av, char *flag, int args_number, char ***args)
{
    int flag_index = flag_exists(flag, av);

    if (flag_index < 0)
        return false;
    if (!args_number)
        return true;
    if (args_number == -1)
        *args = get_arguments_with_no_limit(av, flag_index);
    else
        *args = get_arguments(av, flag_index, args_number);
    if (!*args)
        return false;
    return true;
}
