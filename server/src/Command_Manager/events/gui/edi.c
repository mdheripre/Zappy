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
/**
 * @brief Handles the "edi" event for the GUI client.
 *
 * Sends an egg destruction notification to the GUI client.
 *
 * @param ctx Pointer to the server context (server_t).
 * @param data Pointer to the event data (game_event_t).
 */
void handle_gui_edi(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = server->gui;

    if (!server || !event || !client)
        return;
    dprintf(client->fd, "edi #%d\n", event->data.egg.egg_id);
}
