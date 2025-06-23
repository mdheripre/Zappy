/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_connect_player
*/

#include "game.h"
#include "utils.h"
#include "server.h"
#include "client.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_connect_nbr(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.response
        || !event->data.generic_response.client)
        return;
    client = event->data.generic_response.client;
    dprintf(client->fd, "%s\n", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
