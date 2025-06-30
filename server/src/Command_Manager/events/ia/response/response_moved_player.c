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

bool is_client_alive(server_t *server, client_t *client)
{
    if (!server || !client || !server->clients)
        return false;
    for (list_node_t *node = server->clients->head; node; node = node->next) {
        if (node->data == client)
            return true;
    }
    return false;
}

void on_response_player_moved(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_moved.player;
    client_t *client = player ? player->client : NULL;

    if (!server || !player || !client)
        return;
    if (!is_client_alive(server, client))
        return;
    if (event->data.player_moved.ia_success) {
        dprintf(client->fd, "ok\n");
        EMIT(server->command_manager->dispatcher, EVENT_GUI_PPO, player);
    } else {
        dprintf(client->fd, "ko\n");
    }
}
