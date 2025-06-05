/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_delay
*/
#include "server.h"


/****************************************************************************/
/*                                                                          */
/*                          DELAY COMMAND                                   */
/*                                                                          */
/****************************************************************************/

float get_command_delay(server_t *server, const char *command)
{
    if (!server || !command)
        return 0.0f;
    if (strcmp(command, "Forward") == 0)
        return 7.0f / server->game->frequency;
    if (strcmp(command, "Inventory") == 0)
        return 1.0f / server->game->frequency;
    return 0.0f;
}
