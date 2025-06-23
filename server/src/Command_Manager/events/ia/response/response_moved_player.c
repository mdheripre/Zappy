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
        EMIT(server->command_manager->dispatcher, "gui_ppo", player);
    } else
        dprintf(client->fd, "ko\n");
}
