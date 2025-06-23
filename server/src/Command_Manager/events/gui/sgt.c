/*
** EPITECH PROJECT, 2025
** server
** File description:
** sgt
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Handles the SGT command from a GUI client.
 *
 * Sends the current server frequency (time unit) to the GUI client.
 * The response follows the format defined in the GUI protocol: "sgt T\n",
 * where T is the current frequency of the game server.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_sgt(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;

    if (!server || !client || !server->game)
        return;
    dprintf(client->fd, "sgt %d\n", (int)server->game->frequency);
}
