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

void handle_gui_sbp(void *ctx, void *)
{
    server_t *server = ctx;
    client_t *client = server ? server->gui : NULL;

    if (!client)
        return;
    dprintf(client->fd, "sbp\n");
}
