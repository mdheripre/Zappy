/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_connect_player
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
 * @brief Handle the response to a 'Connect_nbr' request.
 *
 * Retrieves the client and emits a send_response event with the message.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the response event (game_event_t *).
 */
void on_response_connect_nbr(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload;

    if (!server || !event || !event->data.generic_response.response)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = get_client_by_fd(server,
        event->data.generic_response.client_fd);
    payload->message = (char *)event->data.generic_response.response;
    if (!payload->client || !payload->message) {
        free(payload->message);
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
