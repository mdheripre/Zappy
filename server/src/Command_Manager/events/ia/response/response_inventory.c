/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_inventory
*/

#include "server.h"
#include "player.h"
#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the response to an inventory request.
 *
 * Emits a send_response event to deliver the inventory to the client.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the inventory response event.
 */
void on_response_inventory(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload = NULL;

    if (!server || !event || !event->data.generic_response.response)
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
