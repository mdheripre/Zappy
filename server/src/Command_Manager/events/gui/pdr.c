/*
** EPITECH PROJECT, 2025
** server
** File description:
** pdr
*/

#include "command_manager.h"
#include "shared.h"
#include "server.h"
#include "client.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the GUI "pdr" event for player item removal.
 *
 * Sends a "pdr" message to the GUI client when a player removes an item.
 *
 * @param ctx Pointer to the server context (server_t *)
 * @param data Pointer to the game event data (game_event_t *)
 */
void handle_gui_pdr(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    player_t *player = event->data.player_item.player;
    client_t *gui = server->gui;

    if (!server || !event || !player || !gui)
        return;
    dprintf(gui->fd, "pdr #%d %d\n", player->id,
        event->data.player_item.type_item);
}
