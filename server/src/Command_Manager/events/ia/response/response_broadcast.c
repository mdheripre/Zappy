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

/**
 * @brief Handles the response to a broadcast command for an AI client.
 *
 * Sends the broadcast response to the specified client and frees
 * the response memory.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event containing the response and client.
 */
void on_response_broadcast(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.client
        || !event->data.generic_response.response)
        return;
    client = event->data.generic_response.client;
    dprintf(client->fd, "%s", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
