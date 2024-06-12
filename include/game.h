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
    size_t nb_players;
    items_t required_items;
} level_t;

typedef struct player_s {
    char *team_name;
    size_t id;
    items_t *inventory;
    int pos[2];
} player_t;

typedef struct team_s {
    char *name;
    size_t available_slots;
    size_t total_players_connected;
} team_t;

typedef struct game_s {
    size_t initial_team_size;
    size_t frequence;
    size_t map_size[2];
    char **teams;
} game_t;
