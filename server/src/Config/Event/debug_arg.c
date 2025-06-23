/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** debug_arg.c
*/

/****************************************************************************/
/*                                                                          */
/*                              EVENTS FLAGS                                */
/*                                                                          */
/****************************************************************************/

#include "config.h"
#include "utils.h"

/**
 * @brief Handles the "--debug" argument to enable debug mode.
 *
 * Sets the debug flag in the configuration and logs a message
 * indicating that debug mode has been activated.
 *
 * @param ctx Pointer to the config structure.
 * @param data Pointer to the parser structure (not used here).
 */
void debug_arg(void *ctx, void *)
{
    config_t *config = ctx;

    config->debug = true;
    console_log(LOG_INFO, "Debug mode activated");
}
