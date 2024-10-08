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
 * @brief tna command for the GUI
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
int internal_pnw(client_t *client, int fd);

/**
 * @brief pnw command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_pnw(server_t *server, client_t *client);

/**
 * @brief ppo command for internal use of zappy
 * @param client
 * @param fd
 * @return return the status of the execution, 1 for OK
*/
int internal_ppo(client_t *client, int fd);

/**
 * @brief ppo command for the GUI
 * @param server
 * @param client
 * @return return the status of the execution, 1 for OK
*/
int command_ppo(server_t *server, client_t *client);

/**
 * @brief ppo command for internal use of zappy
 * @param client
 * @param fd
 * @return return the status of the execution, 1 for OK
*/
int internal_plv(client_t *client, int fd);

/**
 * @brief Incantation command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int command_plv(server_t *server, client_t *client);


/**
 * @brief pin command for internal use of zappy
 * @param client
 * @param fd
 * @return return the status of the execution, 1 for OK
*/
int internal_pin(client_t *client, int fd);

/**
 * @brief Pin command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int command_pin(server_t *server, client_t *client);

/**
 * @brief sst command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int command_sst(server_t *server, client_t *client);
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

/**
 * @brief Fork command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int fork_command(server_t *server, client_t *client);

/**
 * @brief Eject command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int eject_command(server_t *server, client_t *client);

/**
 * @brief Take command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int take_command(server_t *server, client_t *client);

/**
 * @brief Set command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int set_command(server_t *server, client_t *client);

/**
 * @brief Incantation command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int incantation_command(server_t *server, client_t *client);

/**
 * @brief Broadcast command
 * @param server
 * @param client
 * @return 1 if the command has been successfully executed
*/
int broadcast_command(server_t *server, client_t *client);
