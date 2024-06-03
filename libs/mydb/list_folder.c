/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_folder
*/

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "db.h"

static char **loop_that_list_all(DIR *dir, const char *folder,
    char **file_list, int *file_count)
{
    struct stat entry_stat;
    struct dirent *entry;
    char *entry_path;

    entry = readdir(dir);
    while (entry != NULL) {
        entry_path = malloc(strlen(folder) + strlen(entry->d_name) + 2);
        sprintf(entry_path, "%s/%s", folder, entry->d_name);
        if (stat(entry_path, &entry_stat) == 0 &&
            S_ISREG(entry_stat.st_mode)) {
            file_list = realloc(file_list, sizeof(char *) * (*file_count + 2));
            file_list[*file_count] = strdup(entry->d_name);
            (*file_count)++;
        }
        entry = readdir(dir);
        free(entry_path);
    }
    return file_list;
}

char **db_list_folder_files(const char *folder)
{
    DIR *dir = opendir(folder);
    char **file_list = NULL;
    int file_count = 0;

    if (!dir)
        return NULL;
    file_list = loop_that_list_all(dir, folder, file_list, &file_count);
    if (!file_count) {
        closedir(dir);
        return NULL;
    }
    file_list[file_count] = NULL;
    closedir(dir);
    return file_list;
}

static char *get_file_content(char *file_content, char *field)
{
    char *line_start;
    char *line_end;

    line_start = strstr(file_content, field);
    if (line_start != NULL) {
        line_end = strstr(line_start, "\n");
        if (line_end != NULL)
            memmove(line_start, line_end + 1, strlen(line_end + 1) + 1);
        else
            *line_start = '\0';
    }
    return file_content;
}

static int get_fd(char *folder, char *file, int fd)
{
    char *path = malloc(strlen(folder) + strlen(file) + 2);

    strcpy(path, folder);
    strcat(path, "/");
    strcat(path, file);
    fd = open(path, O_RDWR);
    if (fd == -1) {
        free(path);
        return false;
    }
    free(path);
    return fd;
}

bool db_file_delete_line(char *folder, char *file, char *field)
{
    int fd = 0;
    struct stat st;
    size_t size;
    char *file_content;

    fd = get_fd(folder, file, fd);
    fstat(fd, &st);
    size = st.st_size;
    file_content = malloc(size + 1);
    read(fd, file_content, size);
    file_content[size] = '\0';
    file_content = get_file_content(file_content, field);
    lseek(fd, 0, SEEK_SET);
    ftruncate(fd, 0);
    write(fd, file_content, strlen(file_content));
    free(file_content);
    close(fd);
    return true;
}
