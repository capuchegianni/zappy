/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team_handling
*/

#include "server.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool team_exists(game_t *game, char *name)
{
    for (size_t i = 0; i < game->teams_number; i++) {
        if (!strcmp(game->teams[i].name, name))
            return true;
    }
    return false;
}

static void send_response(client_t *client, team_t *team, game_t *game)
{
    dprintf(client->fd, "%ld\n",
    team->available_slots - team->total_players_connected);
    dprintf(client->fd, "%ld %ld\n", game->x, game->y);
}

void set_player_team(char *team_name, game_t *game, client_t *client)
{
    team_t team;

    for (size_t i = 0; i < game->teams_number; i++) {
        if (!strcmp(game->teams[i].name, team_name)) {
            team = game->teams[i];
            break;
        }
    }
    if (team.available_slots == team.total_players_connected) {
        dprintf(client->fd, "ko\n");
        return;
    }
    team.total_players_connected++;
    client->player->team_name = strdup(team_name);
    send_response(client, &team, game);
}

static void set_player_pos(game_t *game, client_t *client, size_t i)
{
    for (size_t j = 0; j < game->x; j++) {
        if (game->map[i][j].egg_here) {
            client->player->x = j;
            client->player->y = i;
            break;
        }
    }
}

void place_player_on_map(game_t *game, client_t *client)
{
    srand(time(NULL));
    for (size_t i = 0; i < game->y; i++)
        set_player_pos(game, client, i);
    client->player->direction = rand() % 4;
}
