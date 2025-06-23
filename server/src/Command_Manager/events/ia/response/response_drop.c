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

void on_response_drop(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_item.player;

    if (!server || !event || !player || !player->client)
        return;
    dprintf(player->client->fd, event->data.player_item.success ?
        "ok\n" : "ko\n");
    if (event->data.player_item.success) {
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PDR, event);
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PIN, player);
    }
}
