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
 * @brief Static table of default delays (in ticks) for each command.
 *
 * Each entry contains the command name, its base execution time in ticks,
 * and an unused field (set to 0).
 */
static const queued_command_t COMMAND_DELAYS[] = {
    { "Forward", 7, 0, 0},
    { "Right", 7, 0, 0},
    { "Left", 7, 0, 0},
    { "Look", 7, 0, 0},
    { "Inventory", 1, 0, 0},
    { "Broadcast", 7, 0, 0},
    { "Connect_nbr", 0, 0, 0},
    { "Fork", 42, 0, 0},
    { "Eject", 7, 0, 0},
    { "Take", 7, 0, 0},
    { "Set", 7, 0, 0},
    { "Incantation", 0, 0, 0},
};

/**
 * @brief Get the base delay in ticks for a given command string.
 *
 * @param server Unused parameter (placeholder for future use).
 * @param command Full command string (e.g., "Forward\n").
 * @return Delay in ticks, or 0 if the command is unknown or invalid.
 */
int get_command_delay(server_t *, const char *command)
{
    char name[BUFFER_COMMAND_SIZE] = {0};

    if (!command)
        return 0;
    if (!extract_command_name(command, name, sizeof(name)))
        return 0;
    for (size_t i = 0; i < sizeof(COMMAND_DELAYS) / sizeof(COMMAND_DELAYS[0]);
        i++) {
        if (strcmp(COMMAND_DELAYS[i].content, name) == 0)
            return COMMAND_DELAYS[i].ticks_remaining;
    }
    return 0;
}
