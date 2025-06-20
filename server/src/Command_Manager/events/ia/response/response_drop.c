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
    client_t *client, game_event_t *event)
{
    if (event->data.player_item.success) {
        EMIT(server->command_manager->dispatcher, "gui_pdr", event);
        EMIT(server->command_manager->dispatcher, "gui_pin", client->player);
    }
    EMIT(server->dispatcher, "send_response", payload);
}

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

void on_response_drop(void *ctx, void *data)
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
    emit_drop(payload, server, client, event);
}
