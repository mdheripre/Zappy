/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** response_inventory
*/

#include "server.h"
#include "player.h"
#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_inventory(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = event->data.generic_response.client;
    const char *msg = event->data.generic_response.response;

    if (!server || !client || !msg)
        return;
    dprintf(client->fd, "%s", msg);
    free((char *)event->data.generic_response.response);
}
