/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** server_header
*/

#pragma once

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include "struct.h"

/**
 * @brief Open a file descriptor for the socket
 * @return a file descriptor for the new socket, -1 if error
*/
int init_fd(void);

/**
 * @brief Free the clients
 * @param client_t* clients
*/
void free_clients(server_t *server);

/**
 * @brief Initialize the server socket
 * @param char** av
 * @param server_t* server
 * @return 0 if success, 84 if error
*/
int fserver(char **av, server_t *server);

/**
 * @brief Get the input from the client
 * @param server_t* server
 * @param client_t* client
 * @return 0 if success, 84 if error
*/
int init_read_buffer(client_t *client);

/**
 * @brief Execute the command
 * @param server_t* server
 * @param client_t* client
 * @return 0 if success, 1 if error
*/
int execute_command(server_t *server, client_t *client);

/**
 * @brief Check if the path is correct
 * @param int port
 * @return 0 if success, 84 if error
*/
int error_management(int port);

/**
 * @brief Check the bind
 * @param int fd
 * @param struct sockaddr_in* addr
 * @return 0 if success, 84 if error
*/
int check_bind(int fd, struct sockaddr_in *addr);

/**
 * @brief Check the listen
 * @param int fd
 * @return 0 if success, 84 if error
*/
int check_listen(int fd);

/**
 * @brief Reset the client
 * @param client_t* client
*/
void reset_client(client_t *client);

/**
 * @brief is the server running
 * @param new
 * @return true if the server is running, false if not
*/
bool is_running(int new);

/**
 * @brief signal handler for SIGINT
 * @param sig
 * @return void
*/
void sigint_handler(int sig);
