/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** incantation
*/

#include "server.h"
#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            HANDLER COMMANDS                              */
/*                                                                          */
/****************************************************************************/


/**
 * Handle the 'Incantation' command from a client.
 *
 * Adds a GAME_EVENT_START_INCANTATION.
 *
 * @param ctx Server context (server_t *).
 * @param data Client data (client_t *).
 */
void handle_command_incantation(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    player_t *player = client ? client->player : NULL;
    game_event_t *event = NULL;

    if (!server || !client || !player)
        return;
    printf("%d\n", player->id);
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    event->type = GAME_EVENT_START_INCANTATION;
    event->data.generic_response.player_id = client->player->id;
    event->data.generic_response.client_fd = client->fd;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
