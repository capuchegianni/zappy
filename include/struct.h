/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client_struct
*/

#pragma once

#include <arpa/inet.h>

#include "game.h"

#define LEN 1024

typedef struct input_s {
    char *body;
    size_t body_len;
    char **args;
    size_t nb_args;
} input_t;

typedef struct client_s {
    int fd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    bool is_playing;
    input_t *input;
    player_t *player;
} client_t;

typedef struct server_s {
    int fd;
    int port;
    struct sockaddr_in addr;
    socklen_t addrlen;
    game_t *game;
    client_t *clients;
} server_t;


typedef struct commands_s {
    char *name;
    int (*function)(server_t *server, client_t *client);
} commands_t;
