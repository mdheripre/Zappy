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
 * @brief Create a broadcast message event for a client.
 *
 * Allocates and initializes a game_event_t with the message content
 * and client metadata.
 *
 * @param client Pointer to the client sending the broadcast.
 * @param message Broadcast message content.
 * @return Pointer to the created event, or NULL on allocation failure.
 */
static game_event_t *create_broadcast_event(client_t *client,
    const char *message)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return NULL;
    memset(event, 0, sizeof(game_event_t));
    event->type = GAME_EVENT_BROADCAST_MESSAGE;
    event->data.generic_response.client = client;
    event->data.generic_response.response = strdup(message);
    return event;
}

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

    if (!server || !client || !player)
        return;
    if (!message || strlen(message) == 0) {
        dprintf(client->fd, "ko\n");
        return;
    }
    event = create_broadcast_event(client, message);
    if (!event)
        return;
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
