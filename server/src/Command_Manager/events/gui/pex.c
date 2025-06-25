/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pex
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
 * @brief Handles the "pex" event for the GUI client.
 *
 * Sends a "pex" message to the GUI client indicating that a player has
 * performed an expulsion.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the client data (client_t).
 */
void handle_gui_pex(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = client->player;
    client_t *gui = server->gui;

    if (!server || !client || !player || !gui)
        return;
    dprintf(gui->fd, "pex #%d\n", player->id);
}
