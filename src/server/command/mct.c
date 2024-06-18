/*
** EPITECH PROJECT, 2024
** mct.c
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include "server_header.h"

int command_mct(server_t *server, client_t *client)
{
    int ret = 1;

    for (size_t i = 0; i < server->height; ++i) {
        for (size_t j = 0; j < server->width; ++j) {
            ret &= internal_bct(i, j, client->fd);
        }
    }
    return ret;
}
