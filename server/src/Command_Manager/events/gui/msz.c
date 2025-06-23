/*
** EPITECH PROJECT, 2025
** server
** File description:
** msz
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
 * @brief Handles the MSZ command from a GUI client.
 *
 * Constructs and sends the map size information to the GUI client.
 * The response follows the GUI protocol format: "msz X Y\n", where
 * X and Y are the width and height of the game map.
 *
 * @param ctx Pointer to the server instance (cast from void).
 * @param data Pointer to the requesting GUI client (cast from void).
 */
void handle_command_gui_msz(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;

    if (!server || !client || !server->game)
        return;
    dprintf(client->fd, "msz %d %d\n",
        server->game->width, server->game->height);
}
