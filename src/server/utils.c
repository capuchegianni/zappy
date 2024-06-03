/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** utils
*/

#include "server_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

static void modify_current_status(server_t *server, client_t *client)
{
    char *status = get_val_from_key("db/users", client->user->id, "status");

    for (int i = 0; i < LEN; i++) {
        if (server->clients[i].is_connected &&
        server->clients[i].fd != client->fd &&
        strcmp(server->clients[i].user->id, client->user->id) == 0)
            return;
    }
    for (int i = 0; status[i] != '\0'; i++) {
        if (status[i] == '1') {
            status[i] = '0';
            break;
        }
    }
    db_file_delete_line("db/users", client->user->id, "status");
    db_file_write("db/users", client->user->id,
        &(db_t){"status", s_to_t(status)}, false);
}

char **s_to_t(char *str)
{
    char **tab = calloc(2, sizeof(char *));

    tab[0] = strdup(str);
    return tab;
}

void reset_client(server_t *server, client_t *client)
{
    if (client->is_connected)
        modify_current_status(server, client);
    client->append_mode = true;
    client->is_connected = false;
    close(client->fd);
    client->fd = -1;
}

void free_clients(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        free(server->clients[i].input->args);
        if (server->clients[i].input->body)
            free(server->clients[i].input->body);
        free(server->clients[i].input);
        if (server->clients[i].fd > -1)
            close(server->clients[i].fd);
    }
    free(server->clients);
    free(server);
}

int error_management(int port)
{
    if (port < 1024 || port > 65535) {
        printf("Invalid specified port\n");
        return 84;
    }
    return 0;
}
