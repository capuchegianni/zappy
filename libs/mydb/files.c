/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** files
*/

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "db.h"

bool db_file_exists(char *folder, char *file)
{
    DIR *dir = opendir(folder);
    struct dirent *entry;

    if (!dir)
        return false;
    entry = readdir(dir);
    while (entry) {
        if (strcmp(entry->d_name, file) == 0) {
            closedir(dir);
            return true;
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return false;
}

bool db_file_create(char *folder, char *file)
{
    char *path = malloc(strlen(folder) + strlen(file) + 2);

    sprintf(path, "%s/%s", folder, file);
    if (creat(path, 0777) == -1) {
        free(path);
        return false;
    }
    free(path);
    return true;
}

bool db_file_read(char *folder, char *file, char **content)
{
    char *path = malloc(strlen(folder) + strlen(file) + 2);
    int fd = 0;
    int size = 0;

    strcpy(path, folder);
    strcat(path, "/");
    strcat(path, file);
    fd = open(path, O_RDONLY);
    free(path);
    if (fd == -1)
        return false;
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    *content = malloc(size + 1);
    read(fd, *content, size);
    (*content)[size] = '\0';
    close(fd);
    return true;
}

bool db_file_write(char *folder, char *file, db_t *content, bool replace)
{
    char *path = malloc(strlen(folder) + strlen(file) + 2);
    char *content_str = NULL;
    int fd = 0;

    content_str = convert_db_to_tab(content, content_str);
    sprintf(path, "%s/%s", folder, file);
    if (replace)
        fd = open(path, O_WRONLY | O_TRUNC);
    else
        fd = open(path, O_WRONLY | O_APPEND);
    if (fd == -1)
        return false;
    write(fd, content_str, strlen(content_str));
    free(content_str);
    free(path);
    close(fd);
    return true;
}

static void loop(char *token, char **return_str, char *field, char *saveptr)
{
    char *db_field = NULL;
    char *saveptrbis = NULL;

    while (token) {
        db_field = strtok_r(token, SEP, &saveptrbis);
        if (!db_field) {
            token = strtok_r(NULL, "\n", &saveptr);
            continue;
        }
        if (strcmp(db_field, field) == 0) {
            (*return_str) = strdup(token + strlen(field) + 2);
            break;
        }
        token = strtok_r(NULL, "\n", &saveptr);
    }
}

char *get_val_from_key(char *folder, char *file, char *field)
{
    char *content = NULL;
    char *token = NULL;
    char *return_str = NULL;
    char *saveptr = NULL;

    if (!db_file_read(folder, file, &content))
        return NULL;
    token = strtok_r(content, "\n", &saveptr);
    loop(token, &return_str, field, saveptr);
    free(content);
    return return_str;
}
