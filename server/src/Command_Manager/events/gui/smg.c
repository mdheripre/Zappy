/*
** EPITECH PROJECT, 2025
** server
** File description:
** smg
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
 * @brief Handles sending a message to the GUI client.
 *
 * This function formats a message and emits a response event to
 * the GUI client, if one is connected.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the message string to be sent.
 */
void handle_gui_smg(void *ctx, void *data)
{
    server_t *server = ctx;
    const char *message = data;
    client_t *client = server ? server->gui : NULL;

    if (!client || !message)
        return;
    dprintf(client->fd, "smg %s\n", message);
}
