/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** folders
*/

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "db.h"

bool db_folder_exists(void)
{
    DIR *dir = opendir("db");

    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

bool db_folder_create(void)
{
    if (mkdir("db", 0777) == -1)
        return false;
    return true;
}

bool db_folder_child_exists(char *child, bool create)
{
    DIR *dir = opendir("db");
    struct dirent *entry;

    if (!dir)
        return false;
    entry = readdir(dir);
    while (entry) {
        if (strcmp(entry->d_name, child) == 0) {
            closedir(dir);
            return true;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    if (create)
        return db_folder_child_create(child);
    return false;
}

bool db_folder_child_create(char *child)
{
    char *str = malloc(strlen("db/") + strlen(child) + 1);

    if (!str)
        return false;
    strcpy(str, "db/");
    strcat(str, child);
    if (mkdir(str, 0777) == -1) {
        free(str);
        return false;
    }
    free(str);
    return true;
}
