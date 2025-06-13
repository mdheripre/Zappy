/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_take
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the response to a take command.
 *
 * Finds the client by FD and emits a send_response event with the result.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the take response event.
 */
void on_response_take(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;
    response_payload_t *payload = NULL;

    if (!server || !event)
        return;
    client = get_client_by_fd(server, event->data.generic_response.client_fd);
    if (!client)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = strdup(event->data.generic_response.response);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
