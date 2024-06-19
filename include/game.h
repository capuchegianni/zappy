/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#pragma once

#define TIME_UNITS 126

typedef unsigned long size_t;

enum ITEMS {
    FOOD = 50,
    LINEMATE = 30,
    DERAUMERE = 15,
    SIBUR = 10,
    MENDIANE = 10,
    PHIRAS = 8,
    THYSTAME = 5
};

enum DIRECTION {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct items_s {
    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
} items_t;

typedef struct level_s {
    size_t level;
    size_t required_players;
    items_t required_items;
} level_t;

typedef struct player_s {
    char *team_name;
    items_t inventory;
    size_t level;
    size_t x;
    size_t y;
    enum DIRECTION direction;
} player_t;

typedef struct team_s {
    char *name;
    size_t available_slots;
    size_t total_players_connected;
} team_t;

typedef struct tile_s {
    items_t items;
} tile_t;

typedef struct game_s {
    size_t initial_team_size;
    size_t frequence;
    size_t x;
    size_t y;
    team_t *teams;
    size_t teams_number;
    level_t levels[7];
    tile_t **map;
} game_t;

typedef struct client_s client_t;

/**
 * @brief Initialize all levels related data
 * @param game
*/
void init_levels(game_t *game);

/**
 * @brief Initialize the game map
 * @param game
 * @return True if correctly initialized, false otherwise
*/
bool init_map(game_t *game);

/**
 * @brief Free the game map
 * @param game
*/
void free_map(game_t *game);

/**
 * @brief Initialize all items to 0
 * @param items
*/
void init_items(items_t *items);

bool team_exists(game_t *game, char *name);

void set_player_team(char *team_name, game_t *game, client_t *client);
