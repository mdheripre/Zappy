/*
** EPITECH PROJECT, 2025
** server
** File description:
** left
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
 * Handle the 'Left' command from a client.
 *
 * Adds a GAME_EVENT_PLAYER_MOVED event to the game event queue.
 *
 * @param ctx Server context (server_t *).
 * @param data Client data (client_t *).
 */
void handle_command_left(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    player_t *player = client ? client->player : NULL;
    game_event_t *event = NULL;

    if (!server || !client || !player)
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    event->type = EVENT_PLAYER_MOVED;
    event->data.player_moved.player = player;
    event->data.player_moved.ia_success = true;
    event->data.player_moved.direction = TURN_LEFT;
    event->data.player_moved.x = player->x;
    event->data.player_moved.y = player->y;
    event->data.player_moved.orientation = player->orientation;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
