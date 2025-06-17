/*
** EPITECH PROJECT, 2025
** server
** File description:
** fork
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
 * @brief Handle the 'Fork' command from a client.
 *
 * Adds a GAME_EVENT_EGG_LAID event with player's position and team.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_fork(void *ctx, void *data)
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
    event->type = GAME_EVENT_EGG_LAID;
    event->data.egg.player_id = player->id;
    event->data.egg.x = player->x;
    event->data.egg.y = player->y;
    event->data.egg.team_name = player->team_name;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
