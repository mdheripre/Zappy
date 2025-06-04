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
    client_t *client = NULL;
    queued_command_t *cmd = NULL;
    int i = 0;

    for (i = 0; i < server->client_count; i++) {
        client = &server->clients[i];
        if (!client->connected || client->type != CLIENT_UNDEFINED)
            continue;
        cmd = client_peek_command(client);
        if (!cmd)
            continue;
        EMIT(server->dispatcher, "client_identify", client);
    }
}
