/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** reject_client
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                             METHODS SERVER                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Rejects a client from the server with an error message.
 *
 * Sends a "ko" response to the client, logs the reason, and triggers
 * the client removal via the server's vtable if the client is found.
 *
 * @param server Pointer to the server instance.
 * @param client Pointer to the client to reject.
 * @param reason String describing the reason for rejection.
 */
void reject_client(server_t *server, client_t *client, const char *reason)
{
    write(client->fd, "ko\n", 3);
    console_log(LOG_WARNING, "%s (fd=%d)", reason, client->fd);
    for (int i = 0; i < server->client_count; i++) {
        if (&server->clients[i] == client) {
            server->vtable->remove_client(server, i);
            return;
        }
    }
}
