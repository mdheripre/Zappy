/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager_identify
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                        PROCESS IDENTIFY                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Processes identification for all undefined clients.
 *
 * Iterates through all connected clients with undefined type,
 * checks if they have a queued command, and emits a "client_identify" event.
 *
 * @param server Pointer to the server structure.
 */
void process_identify(command_manager_t *, server_t *server)
{
    list_node_t *node = NULL;
    list_node_t *next = NULL;
    client_t *client = NULL;

    if (!server || !server->clients)
        return;
    for (node = server->clients->head; node; node = next) {
        next = node->next;
        client = node->data;
        if (!client || !client->connected || client->type != CLIENT_UNDEFINED)
            continue;
        if (!client_peek_command(client))
            continue;
        EMIT(server->dispatcher, EVENT_CLIENT_IDENTIFY, client);
    }
}
