/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_moved_player
*/

#include "client.h"
#include "server.h"
#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the response after a player movement event.
 *
 * Sends "ok" to the client if the movement was successful, otherwise sends
 * "ko". Also emits a GUI update event on successful movement.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event data.
 */
void on_response_player_moved(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_moved.player;
    client_t *client = player ? player->client : NULL;

    if (!server || !player || !client)
        return;
    if (event->data.player_moved.ia_success) {
        dprintf(client->fd, "ok\n");
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PPO, player);
    } else {
        dprintf(client->fd, "ko\n");
    }
}
