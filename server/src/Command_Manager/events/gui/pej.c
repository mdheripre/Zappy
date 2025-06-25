/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pej
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
 * @brief Handles the "pej" event for the GUI client.
 *
 * Sends a "smg pej" message with the player's ID to the GUI client.
 *
 * @param ctx Pointer to the server context (server_t *)
 * @param data Pointer to the player data (player_t *)
 */
void handle_gui_pej(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui = NULL;

    if (!server || !player)
        return;
    gui = server->gui;
    if (!gui)
        return;
    dprintf(gui->fd, "smg pej #%d\n", player->id);
}
