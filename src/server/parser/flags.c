/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** flags
*/

#include "server_header.h"

bool store_arguments_in_server(server_t *server, char **av)
{
    if (!clients_flag(server, av))
        return false;
    if (!frequency_flag(server, av))
        return false;
    if (!height_flag(server, av))
        return false;
    if (!width_flag(server, av))
        return false;
    if (!port_flag(server, av))
        return false;
    if (!teams_flag(server, av))
        return false;
    return true;
}
