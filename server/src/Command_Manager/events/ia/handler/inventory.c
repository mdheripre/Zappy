/*
** EPITECH PROJECT, 2025
** server
** File description:
** inventory
*/

#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                        HANDLER COMMAND                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle the 'Inventory' command from a client.
 *
 * Adds a GAME_EVENT_CHECK_INVENTORY event to the queue.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_inventory(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = client ? client->player : NULL;
    game_event_t *event = NULL;

    if (!server || !client || !player)
        return;
    event = calloc(1, sizeof(game_event_t));
    if (!event)
        return;
    event->type = GAME_EVENT_CHECK_INVENTORY;
    event->data.generic_response.client = client;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
