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

static const queued_command_t COMMAND_DELAYS[] = {
    { "Forward", 7.0f },
    { "Right", 7.0f },
    { "Left", 7.0f },
    { "Look", 7.0f },
    { "Inventory", 1.0f },
    { "Broadcast", 7.0f },
    { "Connect_nbr", 0.0f },
    { "Fork", 42.0f },
    { "Eject", 7.0f },
    { "Take", 7.0f },
    { "Set", 7.0f },
    { "Incantation", 0.0f },
};

float get_command_delay(server_t *server, const char *command)
{
    if (!server || !command)
        return 0.0f;
    for (size_t i = 0; i < sizeof(COMMAND_DELAYS) / sizeof(COMMAND_DELAYS[0]);
        i++) {
        if (strcmp(COMMAND_DELAYS[i].content, command) == 0)
            return COMMAND_DELAYS[i].time_remaining / server->game->frequency;
    }
    return 0.0f;
}
