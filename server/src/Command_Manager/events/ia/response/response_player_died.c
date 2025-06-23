/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_player_died
*/

#include "command_manager.h"
#include "game.h"
#include "player.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

static void notify_player_death(server_t *server, player_t *player)
{
    client_t *client = player ? player->client : NULL;

    if (client)
        dprintf(client->fd, "dead\n");
    EMIT(server->command_manager->dispatcher, "gui_pdi", player);
}

void on_response_player_died(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_died.player;
    client_t *client = player ? player->client : NULL;

    if (!server || !player)
        return;
    notify_player_death(server, player);
    server->game->players->methods->remove(server->game->players, player);
    if (client)
        server->vtable->remove_client(server, client);
}
