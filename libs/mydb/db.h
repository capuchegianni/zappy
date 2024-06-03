/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** db
*/

#pragma once

#define SEP "::"

#include <stdbool.h>

typedef struct db_s {
    char *field;
    char **values;
} db_t;

// Folder functions

/**
 * @brief Check if the database folder exists.
 * @return true if the database folder exists, false otherwise.
*/
bool db_folder_exists(void);

/**
 * @brief Create the database folder.
 * @return true if the database folder was successfully created or already
 * exists, false otherwise.
*/
bool db_folder_create(void);

/**
 * @brief Check if a child folder exists in the database folder.
 * @param child The name of the child folder.
 * @param create If true, the child folder will be created if it doesn't exist.
 * @return true if the child folder exists (or was created), false otherwise.
*/
bool db_folder_child_exists(char *child, bool create);

/**
 * @brief Create a child folder in the database folder.
 * @param child The name of the child folder.
 * @return true if the child folder was successfully created or already exists,
 * false otherwise.
*/
bool db_folder_child_create(char *child);

/**
 * @brief List all files in a given folder.
 * @param folder The name of the folder.
 * @return An array of strings containing the names of the files in the folder.
*/
char **db_list_folder_files(const char *folder);


// File functions

/**
 * @brief Check if a file exists in a specific folder.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @return true if the file exists, false otherwise.
*/
bool db_file_exists(char *folder, char *file);

/**
 * @brief Create a file in a specific folder.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @return true if the file was successfully created or already exists,
 * false otherwise.
*/
bool db_file_create(char *folder, char *file);

/**
 * @brief Read the content of a file in a specific folder.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @param content A pointer to a char pointer where the content of the file
 * will be stored.
 * @return true if the file was successfully read, false otherwise.
*/
bool db_file_read(char *folder, char *file, char **content);

/**
 * @brief Write content to a file in a specific folder.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @param content The content to write to the file.
 * @param replace If true, the file will be overwritten if it already exists.
 * @return true if the file was successfully written, false otherwise.
*/
bool db_file_write(char *folder, char *file, db_t *content, bool replace);

/**
 * @brief Delete the line beginning with a specific field in a file.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @param field The name of the field.
 * @return true if the line was successfully deleted, false otherwise.
*/
bool db_file_delete_line(char *folder, char *file, char *field);

/**
 * @brief Get the value of a field in a file.
 * @param folder The name of the folder.
 * @param file The name of the file.
 * @param field The name of the field.
 * @return The value of the field, or NULL if the field doesn't exist.
*/
char *get_val_from_key(char *folder, char *file, char *field);


// Misc functions

/**
 * @brief Convert a string to a db_t structure.
 * @param field Field of the value.
 * @param value Value of the field
 * @return A new allocated db_t.
*/
db_t *convert_tab_to_db(char *field, char **value, db_t *content);

/**
 * @brief Convert a db_t structure to a string.
 * @param content The db_t structure to convert.
 * @param content_str A pointer to a char pointer where the string will
 * be stored.
*/
char *convert_db_to_tab(db_t *content, char *content_str);
