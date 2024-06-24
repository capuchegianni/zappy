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

bool set_player_team(char *team_name, game_t *game, client_t *client)
{
    team_t *teams = game->teams;
    size_t i = 0;

    for (; i < game->teams_number; i++) {
        if (!strcmp(game->teams[i].name, team_name))
            break;
    }
    if (teams[i].available_slots == teams[i].total_players_connected) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    teams[i].total_players_connected++;
    client->player->team_name = strdup(team_name);
    client->is_playing = true;
    send_response(client, &teams[i], game);
    return true;
}

static void set_player_pos(game_t *game, client_t *client, size_t i)
{
    for (size_t j = 0; j < game->x; j++) {
        if (game->map[i][j].egg_here) {
            client->player->x = j;
            client->player->y = i;
            game->map[i][j].egg_here--;
            game->map[i][j].player_here++;
            break;
        }
    }
}

void place_player_on_map(game_t *game, client_t *client)
{
    srand(time(NULL));
    for (size_t i = 0; i < game->y; i++)
        set_player_pos(game, client, i);
    client->player->direction = (rand() % 4) + 1;
    client->player->inventory.food = 10;
}
