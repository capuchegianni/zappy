/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** argument_parser
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t tablen(char **tab)
{
    size_t i = 0;

    for (; tab[i]; i++);
    return i;
}

static void free_tab(char **tab)
{
    for (size_t i = 0; tab[i]; i++) {
        free(tab[i]);
    }
    free(tab);
}

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
    return args;
}

bool flag_parser(char **av, char *flag, size_t args_number, char ***args)
{
    int flag_index = flag_exists(flag, av);

    if (flag_index < 0)
        return false;
    if (flag_index + args_number >= tablen(av))
        return false;
    if (!args) {
        if (!args_number)
            return true;
        return false;
    }
    *args = get_arguments(av, flag_index, args_number);
    if (*args == NULL)
        return false;
    return true;
}
