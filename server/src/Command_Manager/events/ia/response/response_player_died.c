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

/**
 * @brief Handle a player's death and notify the client.
 *
 * Sends "dead" to the player and removes them from the server.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the death event (game_event_t *).
 */
void on_response_player_died(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = NULL;
    int client_fd = -1;
    int index = -1;

    if (!server || !event)
        return;
    player = find_player_by_id(server->game,
        event->data.player_died.player_id);
    if (!player)
        return;
    client_fd = get_client_fd_by_player(server, player, &index);
    if (client_fd != -1)
        dprintf(client_fd, "dead\n");
    EMIT(server->command_manager->dispatcher, "gui_pdi", player);
    server->game->players->methods->remove(server->game->players, player);
    server->vtable->remove_client(server, index);
}
