/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** db_struct
*/

#include "db.h"

#include <stdlib.h>
#include <string.h>

db_t *convert_tab_to_db(char *field, char **value, db_t *content)
{
    content->field = field;
    content->values = value;
    return content;
}

char *convert_db_to_tab(db_t *content, char *content_str)
{
    int len = 0;

    len += strlen(content->field) + 1;
    for (int i = 0; content->values && content->values[i]; i++)
        len += strlen(content->values[i]) + 1;
    content_str = malloc(sizeof(char *) * (len + 1) + 1);
    strcpy(content_str, content->field);
    strcat(content_str, SEP);
    for (int i = 0; content->values && content->values[i]; i++) {
        strcat(content_str, content->values[i]);
        if (content->values[i + 1])
            strcat(content_str, SEP);
    }
    for (int i = 0; content->values && content->values[i]; i++)
        free(content->values[i]);
    free(content->values);
    strcat(content_str, "\n");
    return content_str;
}
