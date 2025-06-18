/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** edi
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

void handle_gui_edi(void *ctx, void *data)
{
    server_t *server = ctx;
    egg_t *egg = data;
    client_t *client = server->vtable->get_gui(server);

    if (!server || !egg || !client)
        return;
    dprintf(client->fd, "edi #%d\n", egg->id);
}
