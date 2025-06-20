/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_take
*/

#include "client.h"
#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/** * @brief Emit the take response to the client.
 *
 * Sends the response payload to the client and updates the GUI pin.
 *
 * @param payload Pointer to payload.
 * @param server Pointer to the server instance.
 * @param client Pointer to the client receiving the response.
 */
static void emit_take(response_payload_t *payload, server_t *server,
    client_t *client, game_event_t *event)
{
    if (event->data.player_item.success) {
        EMIT(server->command_manager->dispatcher, "gui_pgt", event);
        EMIT(server->command_manager->dispatcher, "gui_pin", client->player);
    }
    EMIT(server->dispatcher, "send_response", payload);
}

/**
 * @brief Create a response payload for the take command.
 *
 * Allocates memory for a response payload and initializes it with the client
 * and success message.
 *
 * @param client Pointer to the client associated with the response.
 * @param success Indicates if the take command was successful.
 * @return Pointer to the created response payload, or NULL on failure.
 */
static response_payload_t *create_response_payload(client_t *client,
    bool success)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));

    if (!payload)
        return NULL;
    payload->client = client;
    payload->message = strdup(success ? "ok\n" : "ko\n");
    if (!payload->message) {
        free(payload);
        return NULL;
    }
    return payload;
}

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
    player_t *player = find_player_by_id(server->game,
        event->data.player_item.player_id);
    client_t *client = get_client_by_player(server, player, NULL);
    response_payload_t *payload = NULL;

    if (!server || !event || !client)
        return;
    payload = create_response_payload(client, event->data.player_item.success);
    if (!payload)
        return;
    emit_take(payload, server, client, event);
}
