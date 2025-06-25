/*
** EPITECH PROJECT, 2025
** server
** File description:
** sbp
*/

#include "game.h"
#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Sends a "sbp" (syntax error) message to the GUI client.
 *
 * @param ctx Pointer to the server context.
 * @param Unused parameter.
 */
void handle_gui_sbp(void *ctx, void *)
{
    server_t *server = ctx;
    client_t *client = server ? server->gui : NULL;

    if (!client)
        return;
    dprintf(client->fd, "sbp\n");
}
