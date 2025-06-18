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
 * @brief Create a response payload for a player who has been ejected.
 *
 * Finds the player and client, then prepares the payload using the event data.
 *
 * @param server Pointer to the server instance.
 * @param event Pointer to the game event.
 * @return Pointer to the response payload, or NULL on failure.
 */
static response_payload_t *client_ejected(server_t *server,
    game_event_t *event)
{
    player_t *player = find_player_by_id(server->game,
        event->data.generic_response.player_id);
    client_t *client = get_client_by_player(server, player, NULL);
    response_payload_t *payload = NULL;

    if (!client || !event->data.generic_response.response)
        return NULL;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return NULL;
    payload->client = client;
    payload->message = (char *)event->data.generic_response.response;
    return payload;
}

/**
 * @brief Create a response payload for the player who initiated the eject.
 *
 * Retrieves the client from the event and builds the response payload.
 *
 * @param server Pointer to the server instance.
 * @param event Pointer to the game event.
 * @return Pointer to the response payload, or NULL on failure.
 */
static response_payload_t *owner_eject(server_t *server, game_event_t *event)
{
    client_t *client = get_client_by_fd(server,
        event->data.generic_response.client_fd);
    response_payload_t *payload = NULL;

    if (!client || !event->data.generic_response.response)
        return NULL;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return NULL;
    payload->client = client;
    payload->message = (char *)event->data.generic_response.response;
    if (strcmp("ok\n", event->data.generic_response.response) == 0)
        EMIT(server->command_manager->dispatcher, "gui_pex", client);
    return payload;
}

/**
 * @brief Handle the response event related to a player ejection.
 *
 * Dispatches a response to the ejected player or the ejecting owner.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the ejection event.
 */
void on_response_eject(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    response_payload_t *payload = NULL;

    if (event->type == GAME_EVENT_RESPONSE_PLAYER_EJECTED)
        payload = client_ejected(server, event);
    else if (event->type == GAME_EVENT_RESPONSE_PLAYER_OWNER_EJECTED)
        payload = owner_eject(server, event);
    if (payload)
        EMIT(server->dispatcher, "send_response", payload);
}
