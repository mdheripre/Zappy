/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** help_arg.c
*/

#include "config.h"

/****************************************************************************/
/*                                                                          */
/*                              EVENTS FLAGS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handler for the "-h" or "--help" argument.
 *
 * Displays the help message and sets the config to exit afterward.
 *
 * @param ctx Pointer to the config structure (cast from void).
 * @param unused Unused argument, ignored.
 */
void help_arg(void *ctx, void *)
{
    config_t *config = ctx;

    config->methods->help_message();
    config->exit = true;
}
