/*
** EPITECH PROJECT, 2025
** server
** File description:
** eject
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
 * @brief Handle the 'Eject' command from a client.
 *
 * Adds a GAME_EVENT_PLAYER_EJECT event to the queue.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_eject(void *ctx, void *data)
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
    event->type = GAME_EVENT_PLAYER_EJECT;
    event->data.generic_response.client_fd = client->fd;
    event->data.generic_response.player_id = player->id;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
