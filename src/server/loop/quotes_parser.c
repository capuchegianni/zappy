/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** quotes_parser
*/

#include "server_header.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int get_quotes_number(char *buffer)
{
    int quotes = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"')
            quotes++;
    }
    return quotes;
}

static void remove_quotes(char **buffer)
{
    char *new_buffer = calloc(strlen(*buffer) - 1, sizeof(char));
    int j = 0;

    for (int i = 0; (*buffer)[i] != '\0'; i++) {
        if ((*buffer)[i] != '"') {
            new_buffer[j] = (*buffer)[i];
            j++;
        }
    }
    free(*buffer);
    *buffer = new_buffer;
}

int quotes_parser(client_t *client)
{
    int quotes = 0;

    for (int i = 1; client->input->args[i]; i++) {
        quotes = get_quotes_number(client->input->args[i]);
        if (!quotes || quotes % 2) {
            dprintf(client->fd, "Invalid number of quotes\n");
            return 1;
        }
        remove_quotes(&client->input->args[i]);
        if (strlen(client->input->args[i]) == 0) {
            dprintf(client->fd, "Empty quotes\n");
            return 1;
        }
    }
    return 0;
}

bool space_remover(char **buffer)
{
    bool between_quotes = false;
    int quotes = 0;

    for (int i = 0; (*buffer)[i]; i++) {
        if ((*buffer)[i] == '"') {
            between_quotes = !between_quotes;
            quotes++;
        }
        if ((*buffer)[i] != ' ' && (*buffer)[i] != '"' &&
            !between_quotes && quotes) {
            return false;
        }
        if ((*buffer)[i] == ' ' && between_quotes)
            (*buffer)[i] = '`';
    }
    return true;
}

static void assign_spaces(client_t *client, int i, int j)
{
    if (client->input->args[i][j] == '`')
        client->input->args[i][j] = ' ';
}

void replace_backticks(client_t *client)
{
    for (int i = 0; client->input->args[i]; i++) {
        for (int j = 0; client->input->args[i][j]; j++) {
            assign_spaces(client, i, j);
        }
    }
}
