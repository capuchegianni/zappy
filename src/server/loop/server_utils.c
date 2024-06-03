/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** server_utils
*/

#include "server_header.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

int check_bind(int fd, struct sockaddr_in *addr)
{
    if (bind(fd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        printf("Error on bind: %s\n", strerror(errno));
        return 84;
    }
    return 0;
}

int check_listen(int fd)
{
    if (listen(fd, 256) < 0) {
        printf("Error on listen: %s\n", strerror(errno));
        return 84;
    }
    return 0;
}

int init_fd(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0) {
        printf("Error on socket: %s\n", strerror(errno));
        return -1;
    }
    return fd;
}

bool is_running(int new)
{
    static bool alive;

    if (new != -1)
        alive = new;
    return alive;
}

void sigint_handler(int sig)
{
    (void)sig;
    is_running(false);
}
