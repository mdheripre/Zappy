/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_event_not_found
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                               EVENT GLOBAL                               */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Handles events that are not found in the dispatcher.
 *
 * Logs a warning and notifies the client if the unknown event is a command,
 * otherwise logs the event as ignored.
 *
 * @param self Pointer to the dispatcher instance.
 * @param event Name of the event that was not found.
 * @param data Pointer to the client structure (client_t *).
 */
void on_event_not_found(dispatcher_t *, const char *event, void *data)
{
    client_t *client = data;

    if (!event || !client)
        return;
    if (strncmp(event, "command_ia_", 11) == 0 ||
        strncmp(event, "command_gui_", 12) == 0) {
        console_log(LOG_WARNING,
            "Unknown command \"%s\" from client fd=%d", event, client->fd);
        write(client->fd, "ko\n", 3);
    } else
        console_log(LOG_INFO, "Ignored unknown event \"%s\"", event);
}
