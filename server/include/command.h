/*
** EPITECH PROJECT, 2024
** command.h
** File description:
** B-YEP-400-LIL-4-1-zappy-nicolas.pechart
*/

#pragma once

#include "server.h"

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

/**
 * @brief bct command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_bct(server_t *server, client_t *client);

/**
 * @brief bct command for internal use of zappy
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int internal_bct(int x, int y, int fd, server_t *server);

/**
 * @brief mct command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_mct(server_t *server, client_t *client);

/**
 * @brief bct command for internal use of zappy
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_tna(server_t *server, client_t *client);


// Commands for AI/server communication

/**
 * @brief Forward command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int forward_command(server_t *server, client_t *client);

/**
 * @brief Right command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int right_command(server_t *server, client_t *client);

/**
 * @brief Left command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int left_command(server_t *server, client_t *client);

/**
 * @brief Look command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int look_command(server_t *server, client_t *client);

/**
 * @brief Inventory command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int inventory_command(server_t *server, client_t *client);

/**
 * @brief Connect_nbr command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int connect_nbr_command(server_t *server, client_t *client);
