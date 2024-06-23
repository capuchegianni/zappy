/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** utils
*/

#include "server.h"
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

void set_player_id(player_t *player)
{
    static size_t id = 1;

    player->id = id;
    id++;
}

static void clear_input(client_t *client)
{
    client->player->id = 0;
    client->player->level = 1;
    for (int i = 0; i < 10; i++) {
        client->input[i].args = NULL;
        client->input[i].nb_args = 0;
        client->input[i].body = NULL;
        client->input[i].body_len = 0;
        client->input[i].exec_time = 0;
    }
}

static void reset_player(player_t *player)
{
    init_items(&player->inventory);
    player->id = 0;
    player->level = 1;
    player->x = 0;
    player->y = 0;
    player->last_command_time = 0;
    player->in_incantation = 0;
    player->direction = NORTH;
    player->team_name = NULL;
}

static void remove_from_team(game_t *game, player_t *player)
{
    team_t *team = malloc(sizeof(team_t));

    if (!player->team_name)
        return;
    for (size_t i = 0; i < game->teams_number; i++) {
        if (!strcmp(game->teams[i].name, player->team_name)) {
            team = &game->teams[i];
            break;
        }
    }
    team->total_players_connected--;
    free(player->team_name);
}

void reset_client(server_t *server, client_t *client)
{
    client->is_playing = false;
    client->is_graphic = false;
    close(client->fd);
    for (int i = 0; i < FD_SETSIZE; ++i)
        if (client->fd > -1 && server->clients[i].is_graphic)
            dprintf(server->clients[i].fd, "pdi %li\n", client->player->id);
    client->fd = -1;
    remove_from_team(server->game, client->player);
    reset_player(client->player);
    clear_input(client);
}

void free_clients(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->clients[i].fd > -1)
            close(server->clients[i].fd);
        if (server->clients[i].player->team_name)
            free(server->clients[i].player->team_name);
        free(server->clients[i].player);
    }
    free(server->clients);
    for (size_t i = 0; i < server->game->teams_number; i++)
        free(server->game->teams[i].name);
    free(server->game->teams);
    free_map(server->game);
    free(server->game);
    free(server);
}
