/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** pmv
*/

#include "client.h"
#include "command_manager.h"
#include "server.h"
#include "utils.h"
#include <stdio.h>

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handles the "pmv" event for the GUI.
 *
 * Sends a "smg pmv" message to the GUI client with the player's ID.
 *
 * @param ctx Pointer to the server context (server_t*).
 * @param data Pointer to the player data (player_t*).
 */
void handle_gui_pmv(void *ctx, void *data)
{
    server_t *server = ctx;
    player_t *player = data;
    client_t *gui = NULL;

    if (!server || !player)
        return;
    gui = server->gui;
    if (!gui)
        return;
    dprintf(gui->fd, "smg pmv #%d\n", player->id);
}
