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

/**
 * @brief Handles the response for the "look" command from an AI client.
 *
 * Sends the generated response to the client and frees the response memory.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the game event containing the response and client
 * info.
 */
void on_response_look(void *ctx, void *data)
{
    server_t *server = ctx;
    game_event_t *event = data;
    client_t *client = NULL;

    if (!server || !event || !event->data.generic_response.response)
        return;
    client = event->data.generic_response.client;
    if (!client || !is_client_alive(server, client))
        return;
    dprintf(client->fd, "%s", event->data.generic_response.response);
    free((char *)event->data.generic_response.response);
}
