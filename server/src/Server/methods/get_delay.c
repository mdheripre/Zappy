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

/**
 * @brief Static table of default command delays in time units.
 *
 * Each entry defines a command name and its base delay before execution.
 */
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

/**
 * @brief Compute the execution delay for a given command.
 *
 * @param server Pointer to the server (used to access frequency).
 * @param command Full command line string.
 * @return Delay in seconds, or 0.0f if unknown or invalid.
 */
float get_command_delay(server_t *server, const char *command)
{
    char cmd_name[BUFFER_COMMAND_SIZE];

    if (!server || !command)
        return 0.0f;
    if (!extract_command_name(command, cmd_name, sizeof(cmd_name)))
        return 0.0f;
    for (size_t i = 0;
            i < sizeof(COMMAND_DELAYS) / sizeof(COMMAND_DELAYS[0]); i++) {
        if (strcmp(COMMAND_DELAYS[i].content, cmd_name) == 0) {
            return COMMAND_DELAYS[i].time_remaining / server->game->frequency;
        }
    }
    return 0.0f;
}
