/*
** EPITECH PROJECT, 2025
** server
** File description:
** response_look
*/

#include "game.h"
#include "player.h"
#include "utils.h"
#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                        RESPONSE COMMAND                                  */
/*                                                                          */
/****************************************************************************/

void on_response_look(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.response)
        return;
    client = event->data.generic_response.client;
    if (!client)
        return;
    dprintf(client->fd, "%s", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
