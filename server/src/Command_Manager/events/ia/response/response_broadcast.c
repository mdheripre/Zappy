/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_broadcast
*/

#include "game.h"
#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_broadcast(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.client
        || !event->data.generic_response.response)
        return;
    client = event->data.generic_response.client;
    dprintf(client->fd, "%s\n", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
