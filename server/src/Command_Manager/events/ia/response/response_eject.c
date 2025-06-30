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
 * @brief Handles the response to an eject command for a player.
 *
 * Sends the appropriate response message to the client and emits GUI events
 * based on the type of eject event received.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the event data containing the response and client
 * info.
 */
void on_response_eject(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    const char *msg = event->data.generic_response.response;
    client_t *client = event->data.generic_response.client;

    if (!server || !event || !client ||
        !is_client_alive(server, client) || !msg)
        return;
    dprintf(client->fd, "%s", msg);
    if (event->type == EVENT_RESP_PLAYER_OWNER_EJECTED &&
        strcmp(msg, "ok\n") == 0) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PEX, client);
    }
    if (event->type == EVENT_RESP_PLAYER_EJECTED)
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PPO,
            client->player);
    free((char *)event->data.generic_response.response);
}
