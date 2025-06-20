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
    player_t *player = find_player_by_id(server->game,
        event->data.egg.player_id);
    client_t *client = get_client_by_player(server, player, NULL);

    if (!server || !event || !client)
        return;
    dprintf(client->fd, "ok\n");
    EMIT(server->command_manager->dispatcher, "gui_enw", event);
}
