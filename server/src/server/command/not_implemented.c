/*
** EPITECH PROJECT, 2024
** not_implemented.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include "stdio.h"
#include "command.h"

int command_not_impl(server_t *server, client_t *client)
{
    (void)server;
    (void)client;
    printf("NOT IMPLEMENTED YET\n");
    dprintf(client->fd, "ko");
    return 1;
}
