/*
** EPITECH PROJECT, 2025
** server
** File description:
** ebo
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Builds the "ebo" message for a given egg.
 *
 * @param egg Pointer to the egg_t structure.
 * @return Dynamically allocated string containing the message,
 * or NULL on failure.
 */
static char *build_ebo_message(const egg_t *egg)
{
    char buffer[BUFFER_SIZE];

    if (!egg)
        return NULL;
    snprintf(buffer, sizeof(buffer), "ebo #%d\n", egg->id);
    return strdup(buffer);
}

/**
 * @brief Handles the GUI "ebo" event by sending the
 * appropriate message to the GUI client.
 *
 * @param ctx Pointer to the server_t structure.
 * @param data Pointer to the egg_t structure.
 */
void handle_gui_ebo(void *ctx, void *data)
{
    server_t *server = ctx;
    egg_t *egg = data;
    char *message = NULL;

    if (!server || !egg || !server->gui)
        return;
    message = build_ebo_message(egg);
    if (!message)
        return;
    dprintf(server->gui->fd, "%s", message);
    free(message);
}
