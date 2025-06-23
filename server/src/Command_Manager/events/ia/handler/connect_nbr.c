/*
** EPITECH PROJECT, 2025
** server
** File description:
** connect_nbr
*/

#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             AI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the 'Connect_nbr' command from a client.
 *
 * Adds a GAME_EVENT_CONNECT_NBR event to the queue.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_connect_nbr(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    game_event_t *event = NULL;

    if (!server || !client || !client->player)
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    memset(event, 0, sizeof(game_event_t));
    event->type = GAME_EVENT_CONNECT_NBR;
    event->data.generic_response.client = client;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
