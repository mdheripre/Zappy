/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_send_respons
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                              RESPONSE                                    */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Sends a message to a client and frees the response payload.
 *
 * Writes the message directly to the client's socket, then frees both
 * the message string and the payload structure.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the response payload.
 */
void on_send_response(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    response_payload_t *payload = (response_payload_t *)data;

    if (!server || !payload || !payload->client || !payload->message)
        return;
    write(payload->client->fd, payload->message, strlen(payload->message));
    free(payload->message);
    free(payload);
}
