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

/**
 * @brief default command
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_not_impl(server_t *server, client_t *client);

/**
 * @brief pnw command for internal use of zappy
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_pnw(server_t *server, client_t *client);
