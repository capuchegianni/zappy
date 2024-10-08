/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** server
*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

static void init_addr(server_t *server)
{
    server->addrlen = sizeof(server->addr);
    memset(&server->addr, 0, sizeof(server->addr));
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(server->port);
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

static int accept_clients(server_t *server)
{
    int newFd = accept(server->fd, (struct sockaddr *)&server->addr,
    &server->addrlen);

    if (newFd < 0) {
        printf("Error on accept: %s\n", strerror(errno));
        return 84;
    }
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd < 0) {
            server->clients[i].fd = newFd;
            break;
        }
    }
    printf("Client connected\n");
    write(newFd, "WELCOME\n", 8);
    return 0;
}

static int isset_read(server_t *server, client_t *client, fd_set *readfds)
{
    if (FD_ISSET(client->fd, readfds)) {
        if (init_read_buffer(server, client))
            return 84;
    }
    return 0;
}

static int isset_write(server_t *server, client_t *client, fd_set *writefds)
{
    if (FD_ISSET(client->fd, writefds)) {
        if (execute_command(server, client) < 0)
            return 84;
    }
    return 0;
}

static int isset_client_and_server(server_t *server, fd_set *readfds,
    fd_set *writefds)
{
    if (FD_ISSET(server->fd, readfds)) {
        if (accept_clients(server))
            return 84;
    }
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd < 0)
            continue;
        if (isset_read(server, &server->clients[i], readfds))
            return 84;
        if (isset_write(server, &server->clients[i], writefds))
            return 84;
    }
    return 0;
}

static void set_fds(fd_set *readfds, fd_set *writefds, server_t *server)
{
    FD_ZERO(readfds);
    FD_ZERO(writefds);
    FD_SET(server->fd, readfds);
    FD_SET(server->fd, writefds);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd > -1) {
            FD_SET(server->clients[i].fd, readfds);
            FD_SET(server->clients[i].fd, writefds);
        }
    }
}

static int check_connection(server_t *server)
{
    fd_set writefds;
    fd_set readfds;
    struct timeval tv = {10, 10000};

    set_fds(&readfds, &writefds, server);
    if (select(FD_SETSIZE, &readfds, &writefds, NULL, &tv) < 0) {
        if (errno == EINTR)
            return 0;
        printf("Error on select: %s\n", strerror(errno));
        return 84;
    }
    if (server->game->end)
        return 0;
    if (isset_client_and_server(server, &readfds, &writefds))
        return 84;
    update_game(server);
    return 0;
}

static int init_server(server_t *server)
{
    is_running(true);
    signal(SIGINT, sigint_handler);
    init_addr(server);
    if (check_bind(server->fd, &server->addr) || check_listen(server->fd))
        return 84;
    while (is_running(-1) == true) {
        if (check_connection(server))
            return 84;
    }
    printf("Server closed\n");
    return 0;
}

static void client_init(server_t *server, int i)
{
    server->clients[i].fd = -1;
    server->clients[i].is_playing = false;
    server->clients[i].is_graphic = false;
    server->clients[i].player = malloc(sizeof(player_t));
    server->clients[i].player->id = 0;
    server->clients[i].player->direction = NORTH;
    server->clients[i].player->level = 1;
    server->clients[i].player->team_name = NULL;
    server->clients[i].player->x = 0;
    server->clients[i].player->y = 0;
    server->clients[i].player->last_command_time = 0;
    server->clients[i].player->in_incantation = false;
    for (int j = 0; j < 10; j++) {
        server->clients[i].input[j].args = NULL;
        server->clients[i].input[j].nb_args = 0;
        server->clients[i].input[j].body = NULL;
        server->clients[i].input[j].body_len = 0;
        server->clients[i].input[j].exec_time = 0;
    }
    init_items(&server->clients[i].player->inventory);
}

int fserver(server_t *server)
{
    int return_val = 0;

    server->fd = init_fd();
    if (server->fd < 0)
        return 84;
    server->clients = malloc(sizeof(client_t) * FD_SETSIZE);
    if (!server->clients)
        return 84;
    for (int i = 0; i < FD_SETSIZE; i++)
        client_init(server, i);
    return_val = init_server(server);
    close(server->fd);
    free_clients(server);
    return return_val;
}
