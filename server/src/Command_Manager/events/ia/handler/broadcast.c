/*
** EPITECH PROJECT, 2025
** server
** File description:
** broadcast
*/

#include "server.h"
#include "utils.h"
#include "player.h"
#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             AI COMMANDS                                  */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Handle the 'Broadcast' command from a client.
 *
 * Adds a GAME_EVENT_BROADCAST_MESSAGE event with the message content.
 *
 * @param ctx Pointer to the server.
 * @param data Pointer to the client.
 */
void handle_command_broadcast(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    player_t *player = client ? client->player : NULL;
    const char *line = client_peek_command(client)->content;
    const char *message = extract_command_args(line);
    game_event_t *event = NULL;

    if (!server || !client || !player || !message || strlen(message) == 0)
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    memset(event, 0, sizeof(game_event_t));
    event->type = GAME_EVENT_BROADCAST_MESSAGE;
    event->data.generic_response.player_id = client->player->id;
    event->data.generic_response.client_fd = client->fd;
    event->data.generic_response.response = strdup(message);
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
