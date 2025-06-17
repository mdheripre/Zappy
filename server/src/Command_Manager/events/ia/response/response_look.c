/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_look
*/

#include "game.h"
#include "player.h"
#include "utils.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the response to a 'Look' command.
 *
 * Emits a send_response event with the look result for the client.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the look response event.
 */
void on_response_look(void *ctx, void *data)
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
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}
