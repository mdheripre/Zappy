/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_eject
*/

#include "game.h"
#include "utils.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the response to an eject command.
 *
 * Emits a send_response event to inform the client of the result.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the eject response event.
 */
void on_response_eject(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload = NULL;

    if (!server || !event)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = get_client_by_fd(server,
        event->data.generic_response.client_fd);
    payload->message = (char *)event->data.generic_response.response;
    if (!payload->message || !payload->client) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
