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

/**
 * @brief Handles the response for a "take" action by a player.
 *
 * Sends a success ("ok") or failure ("ko") message to the client based
 * on the action result. Emits GUI events if the action was successful.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event data.
 */
void on_response_take(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_item.player;
    client_t *client = player ? player->client : NULL;

    if (!server || !player || !client)
        return;
    dprintf(client->fd, "%s", event->data.player_item.success ? "ok\n" :
        "ko\n");
    if (event->data.player_item.success) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PGT, event);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PIN, player);
    }
}
