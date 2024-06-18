/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** execute
*/

#include "server.h"
#include "command.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

commands_t commands[] = {
    {"msz", 1, command_msz},
    {"bct", 1, command_bct},
    {"mct", 1, command_mct},
    {"tna", 1, NULL},
    {"ppo", 1, NULL},
    {"plv", 1, NULL},
    {"pin", 1, NULL},
    {"sgt", 1, command_sgt},
    {"sst", 1, NULL},
    {NULL, 0, NULL}
};

static void free_client_args(client_t *client)
{
    for (int i = 0; client->input->args[i]; i++)
        free(client->input->args[i]);
    free(client->input->args);
    free(client->input->body);
    client->input->body = NULL;
    client->input->args = calloc(1, sizeof(char *));
}

static int find_cmd(server_t *server, client_t *client)
{
    for (int j = 0; commands[j].name; j++) {
        if (!client->input->args || !client->input->args[0])
            continue;
        if (strcmp(client->input->args[0], commands[j].name) == 0)
            return commands[j].function(server, client);
    }
    return 0;
}

static void execute_cmd(server_t *server, client_t *client)
{
    if (client->player->team_name == NULL) {
        client->player->team_name = malloc(strlen(client->input->args[0]));
        strcpy(client->player->team_name, client->input->args[0]);
        command_msz(server, client);
        command_sgt(server, client);
        return;
    }
    if (!find_cmd(server, client)) {
        if (client->input->args && client->input->args[0]) {
            dprintf(client->fd, "event_failed_input::%s\n",
            client->input->args[0]);
        }
    }
}

static void store_args(server_t *server, client_t *client, char *token,
    char *cmd)
{
    cmd = strtok(token, " ");
    for (int i = 0; cmd; i++) {
        client->input->args = realloc(client->input->args, sizeof(char *) *
        (i + 2));
        if (!client->input->args)
            return;
        client->input->args[i] = strdup(cmd);
        if (!client->input->args[i])
            return;
        client->input->args[i + 1] = NULL;
        cmd = strtok(NULL, " ");
    }
    execute_cmd(server, client);
}

static void parse_buffer(server_t *server, char *buffer, client_t *client)
{
    char *saveptr = NULL;
    char *token = strtok_r(buffer, "\r\n", &saveptr);
    char *cmd = NULL;

    while (token) {
        store_args(server, client, token, cmd);
        token = strtok_r(NULL, "\r\n", &saveptr);
        free(cmd);
    }
    free(token);
}

static bool check_spaces(char *buffer)
{
    for (int i = 0; buffer[i]; i++)
        if (buffer[i] != ' ' && buffer[i] != '\t')
            return true;
    return false;
}

int execute_command(server_t *server, client_t *client)
{
    if (!client->input->body)
        return 0;
    if (!check_spaces(client->input->body)) {
        dprintf(client->fd, "event_failed_input\n");
        free_client_args(client);
        return 0;
    }
    printf("[%s] %s\n", client->player->team_name, client->input->body);
    parse_buffer(server, client->input->body, client);
    free_client_args(client);
    return 0;
}
