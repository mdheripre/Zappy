/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_egg_laid
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_egg_laid(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.egg.player;

    if (!server || !event || !player || !player->client)
        return;
    dprintf(player->client->fd, "ok\n");
    server->game->max_players++;
    EMIT(server->command_manager->dispatcher, "gui_enw", event);
}
