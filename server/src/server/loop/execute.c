/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** execute
*/

#include "server.h"
#include "command.h"
#include "misc.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

commands_t commands[] = {
    {"msz", 1, 0, command_msz},
    {"bct", 1, 0, command_bct},
    {"mct", 1, 0, command_mct},
    {"tna", 1, 0, command_tna},
    {"ppo", 1, 0, command_ppo},
    {"plv", 1, 0, command_plv},
    {"pin", 1, 0, command_pin},
    {"sgt", 1, 0, command_sgt},
    {"sst", 1, 0, command_sst},
    {"msz", 1, 0, command_msz},
    {"bct", 1, 0, command_bct},
    {"mct", 1, 0, command_mct},
    {"tna", 1, 0, command_tna},
    {"Forward", 0, 7, forward_command},
    {"Right", 0, 7, right_command},
    {"Left", 0, 7, left_command},
    {"Look", 0, 7, look_command},
    {"Inventory", 0, 1, inventory_command},
    {"Broadcast", 0, 7, broadcast_command},
    {"Connect_nbr", 0, 0, connect_nbr_command},
    {"Fork", 0, 42, fork_command},
    {"Eject", 0, 7, eject_command},
    {"Take", 0, 7, take_command},
    {"Set", 0, 7, set_command},
    {"Incantation", 0, 300, incantation_command},
    {NULL, 0, 0, NULL}
};

static void move_inputs(input_t input[10])
{
    free(input[0].body);
    input[0].body_len = 0;
    for (size_t i = 0; i < input[0].nb_args; i++)
        free(input[0].args[i]);
    free(input[0].args);
    input[0].nb_args = 0;
    for (int i = 0; i < 9; i++)
        input[i] = input[i + 1];
    input[9].body = NULL;
    input[9].body_len = 0;
    input[9].args = NULL;
    input[9].nb_args = 0;
    input[9].exec_time = 0;
}

static int find_cmd(server_t *server, client_t *client)
{
    for (int i = 0; commands[i].name; i++) {
        if (!client->input[0].args || !client->input[0].args[0])
            continue;
        if (strcmp(client->input[0].args[0], commands[i].name) == 0
        && client->is_graphic == commands[i].isGuiOnly) {
            client->player->last_command_time = time(NULL);
            client->input[1].exec_time = commands[i].timeout;
            return commands[i].function(server, client);
        }
    }
    return 0;
}

static void init_connection_graphic(server_t *server, client_t *client)
{
    client->is_graphic = true;
    client->player->team_name = strdup("GRAPHIC");
    command_msz(server, client);
    command_sgt(server, client);
    command_tna(server, client);
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && !server->clients[i].is_graphic) {
            internal_pnw(&server->clients[i], client->fd);
        }
    }
}

static void handle_new_connection(server_t *server, client_t *client)
{
    if (!strcmp(client->input->args[0], "GRAPHIC")) {
        set_player_id(client->player);
        init_connection_graphic(server, client);
        return;
    }
    if (!team_exists(server->game, client->input->args[0])) {
        write(client->fd, "ko\n", 4);
        return;
    }
    if (!set_player_team(client->input->args[0], server->game, client))
        return;
    set_player_id(client->player);
    place_player_on_map(server->game, client);
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (server->clients[i].fd > -1 && server->clients[i].is_graphic) {
            internal_pnw(client, server->clients[i].fd);
        }
    }
}

static void execute_cmd(server_t *server, client_t *client)
{
    if (client->player->team_name == NULL) {
        handle_new_connection(server, client);
        return;
    }
    if (!find_cmd(server, client)) {
        if (client->input->args && client->input->args[0])
            dprintf(client->fd, "%s\n", client->is_graphic ? "suc" : "ko");
    }
}

static void store_args(server_t *server, client_t *client, char *token,
    char *cmd)
{
    cmd = strtok(token, " ");
    for (int i = 0; cmd; i++) {
        client->input[0].args = realloc(client->input[0].args, sizeof(char *) *
        (i + 2));
        if (!client->input[0].args)
            return;
        client->input[0].args[i] = strdup(cmd);
        if (!client->input[0].args[i])
            return;
        client->input[0].args[i + 1] = NULL;
        cmd = strtok(NULL, " ");
    }
    client->input[0].nb_args = tablen(client->input[0].args);
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

static bool check_for_execution(server_t *server, client_t *client)
{
    time_t now = time(NULL);

    if (!client->input[0].body)
        return false;
    if (!client->is_graphic) {
        if (!server->game->frequence)
            return false;
        if (client->input[0].exec_time / server->game->frequence > 0.5 &&
        (difftime(now, client->player->last_command_time) <
        client->input[0].exec_time / server->game->frequence ||
        client->player->in_incantation))
            return false;
    }
    if (!check_spaces(client->input[0].body)) {
        dprintf(client->fd, "%s\n", client->is_graphic ? "suc" : "ko");
        move_inputs(client->input);
        return false;
    }
    return true;
}

int execute_command(server_t *server, client_t *client)
{
    if (!check_for_execution(server, client))
        return 0;
    if (client->player->team_name) {
        printf("[%s][%ld] %s\n", client->player->team_name ?
        client->player->team_name : "Anonymous", client->player->id,
        client->input[0].body);
    }
    parse_buffer(server, client->input[0].body, client);
    move_inputs(client->input);
    return 0;
}
