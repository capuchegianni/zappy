/*
** EPITECH PROJECT, 2024
** my_ftp
** File description:
** server_header
*/

#pragma once

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#define HELP "USAGE: ./zappy_server -p port -x width -y height "
#define HELP2 "-n name1 name2 ... -c clientsNb -f freq\n"

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
 * @param server_t* server
 * @return 0 if success, 84 if error
*/
int fserver(server_t *server);

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

/**
 * @brief Check if the given flags exists and parse its arguments
 * @param av
 * @param flag
 * @param args_number
 * @param args
 * @return true if a flag exists and the given number of arguments is right
*/
bool flag_parser(char **av, char *flag, int args_number, char ***args);

/**
 * @brief Free a char **
 * @param tab
*/
void free_tab(char **tab);

/**
 * @brief Get the lenght of a char **
 * @param tab
 * @return the size of the tab
*/
size_t tablen(char **tab);

/**
 * @brief Handle -c flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool clients_flag(server_t *server, char **av);

/**
 * @brief Handle -p flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool port_flag(server_t *server, char **av);

/**
 * @brief Handle -n flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool teams_flag(server_t *server, char **av);

/**
 * @brief Handle -y flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool height_flag(server_t *server, char **av);

/**
 * @brief Handle -x flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool width_flag(server_t *server, char **av);

/**
 * @brief Handle -f flag
 * @param server
 * @param av
 * @return true if arguments of the flag have been retrieved correctly
*/
bool frequency_flag(server_t *server, char **av);

/**
 * @brief Store all the arguments for each given flag
 * @param server
 * @param av
 * @return true if all the arguments have been stored correctly
*/
bool store_arguments_in_server(server_t *server, char **av);

/**
 * @brief msz command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_msz(server_t *server, client_t *client);

/**
 * @brief sgt command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_sgt(server_t *server, client_t *client);
