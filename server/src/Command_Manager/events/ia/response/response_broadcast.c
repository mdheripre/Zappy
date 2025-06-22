/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_broadcast
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
 * @brief Create a response payload for a player from an event.
 *
 * @param server Pointer to the server.
 * @param event Pointer to the game event.
 * @return Allocated response payload, or NULL on failure.
 */
static response_payload_t *create_response_payload(server_t *server,
    game_event_t *event)
{
    player_t *player = NULL;
    client_t *target = NULL;
    response_payload_t *payload = NULL;

    if (!server || !event)
        return NULL;
    player = find_player_by_id(server->game,
        event->data.generic_response.player_id);
    target = get_client_by_player(server, player);
    payload = malloc(sizeof(response_payload_t));
    if (!payload || !target)
        return NULL;
    payload->client = target;
    payload->message = (char *)event->data.generic_response.response;
    if (!payload->message) {
        free(payload);
        return NULL;
    }
    return payload;
}

/**
 * @brief Handle a broadcast response event.
 *
 * Emits a send_response event to notify the client.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the broadcast event.
 */
void on_response_broadcast(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload = NULL;

    payload = create_response_payload(server, event);
    if (!payload)
        return;
    EMIT(server->dispatcher, "send_response", payload);
}
