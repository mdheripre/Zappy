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
    game_event_t *event = data;
    client_t *client = server->gui;

    if (!server || !event || !client)
        return;
    dprintf(client->fd, "edi #%d\n", event->data.egg.egg_id);
}
