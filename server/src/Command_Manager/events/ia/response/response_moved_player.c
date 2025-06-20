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
 * @brief Send a response to a player after a move action.
 *
 * Sends "ok" or "ko" based on success of the move.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the move event (game_event_t *).
 */
void on_response_player_moved(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = NULL;
    int fd = -1;

    if (!server || !event)
        return;
    fd = event->data.player_moved.client_fd;
    if (fd < 0)
        return;
    player = find_player_by_id(server->game,
        event->data.player_moved.player_id);
    if (!player)
        return;
    if (event->data.player_moved.ia_success) {
        dprintf(fd, "ok\n");
        EMIT(server->command_manager->dispatcher, "gui_ppo",
            player);
    } else
        dprintf(fd, "ko\n");
}
