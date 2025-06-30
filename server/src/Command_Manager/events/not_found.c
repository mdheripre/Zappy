/*
** EPITECH PROJECT, 2025
** server
** File description:
** not_found
*/

#include "command_manager.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                      CALLBACK FUNCTION                                   */
/*                                                                          */
/****************************************************************************/
/**
 * @brief Handles unknown commands received from clients.
 *
 * Logs a warning and sends a "ko" response to the client if the event
 * corresponds to an unrecognized IA or GUI command.
 *
 * @param self    Pointer to the dispatcher instance (unused).
 * @param event   The event string representing the command.
 * @param data    Pointer to the client_t structure.
 */
void on_command_not_found(dispatcher_t *self, const char *event, void *data)
{
    client_t *client = (client_t *)data;

    (void)self;
    if (!event || !client)
        return;
    if (client->type == CLIENT_GUI) {
        console_log(LOG_WARNING,
            "Unknown command \"%s\" from client fd=%d", event, client->fd);
        write(client->fd, "suc\n", 4);
    } else {
        console_log(LOG_WARNING,
            "Unknown command \"%s\" from gui", event);
        write(client->fd, "ko\n", 3);
    }
}
