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
