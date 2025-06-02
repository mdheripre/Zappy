/*
** EPITECH PROJECT, 2025
** server
** File description:
** broadcast_gui
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                              BROADCAST                                   */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Broadcasts a message to all GUI clients connected to the server.
 *
 * @param self Pointer to the server instance.
 * @param message The message to broadcast.
 */
void server_broadcast_gui(server_t *self, const char *message)
{
    response_payload_t *payload = NULL;
    client_t *client = NULL;
    int i = 0;

    if (!self || !message)
        return;
    for (i = 0; i < self->client_count; i++) {
        client = &self->clients[i];
        if (client->type != CLIENT_GUI)
            continue;
        payload = malloc(sizeof(response_payload_t));
        if (!payload)
            continue;
        payload->client = client;
        payload->message = message;
        EMIT(self->dispatcher, "send_response", payload);
    }
}
