/*
** EPITECH PROJECT, 2025
** server
** File description:
** drop
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
 * @brief Handle the 'Drop' command from a client.
 *
 * Adds a GAME_EVENT_PLAYER_DROP_ITEM event to the queue.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_drop(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    player_t *player = client ? client->player : NULL;
    game_event_t *event = NULL;

    if (!server || !client || !player)
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    event->type = GAME_EVENT_PLAYER_DROP_ITEM;
    event->data.generic_response.client_fd = client->fd;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
