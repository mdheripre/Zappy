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

/**
 * @brief Handles the response for the "connect_nbr" command.
 *
 * Sends the response message to the client and frees the response memory.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event containing the response and client.
 */
void on_response_connect_nbr(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.response
        || !event->data.generic_response.client)
        return;
    client = event->data.generic_response.client;
    if (!client || !is_client_alive(server, client))
        return;
    dprintf(client->fd, "%s", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
