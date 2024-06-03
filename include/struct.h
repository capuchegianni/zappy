/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client_struct
*/

#pragma once

#include <arpa/inet.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <time.h>
#include <uuid/uuid.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define LEN 1024
#define SEP "::"

static const struct timespec TIMEOUT = {0, 100000000};

enum Type {
    SERVER,
    TEAM,
    CHANNEL,
    THREAD,
};

typedef struct message_s {
    char *id;
    char *sender_id;
    char *receiver_id;
    char *message;
    time_t timestamp;
} message_t;

typedef struct thread_s {
    char *id;
    char *name;
    char *description;
    char *body;
    enum Type type;
    char *parent_id;
    char **children_ids;
    time_t timestamp;
} thread_t;

typedef struct user_s {
    char *id;
    char *name;
    bool is_logged;
    char **current_place_id;
} user_t;

typedef struct input_s {
    char *body;
    size_t body_len;
    char **args;
    int nb_args;
} input_t;

typedef struct client_s {
    int fd;
    bool append_mode;
    bool is_connected;
    input_t *input;
    struct sockaddr_in addr;
    socklen_t addrlen;
    enum Type current_place;
    user_t *user;
} client_t;

typedef struct server_s {
    int fd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    int port;
    client_t *clients;
} server_t;


typedef struct commands_s {
    char *name;
    int (*function)(server_t *server, client_t *client);
} commands_t;
