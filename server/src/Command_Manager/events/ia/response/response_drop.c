/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_drop
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

static void emit_drop(response_payload_t *payload, server_t *server,
    client_t *client)
{
    EMIT(server->dispatcher, "send_response", payload);
    EMIT(server->command_manager->dispatcher, "gui_pin", client);
}

void on_response_drop(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = find_player_by_id(server->game,
        event->data.generic_response.player_id);
    client_t *client = get_client_by_player(server, player, NULL);
    response_payload_t *payload = NULL;

    if (!server || !event || !client || !event->data.generic_response.response)
        return;
    payload = malloc(sizeof(response_payload_t));
    if (!payload)
        return;
    payload->client = client;
    payload->message = (char *)event->data.generic_response.response;
    if (!payload->message) {
        free(payload);
        return;
    }
    emit_drop(payload, server, client);
}
