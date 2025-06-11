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
 * @brief Extract the item name from the client's command.
 *
 * @param client Pointer to the client.
 * @param item Buffer to store the extracted item name.
 * @param item_size Size of the item buffer.
 * @return true if extraction succeeded, false otherwise.
 */
static bool extract_drop_item_name(client_t *client, char *item,
    size_t item_size)
{
    if (!client || !client->commands)
        return false;
    return extract_command_arguments(
        client->commands->methods->front(client->commands), item, item_size);
}

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
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    player_t *player = client ? client->player : NULL;
    game_event_t *event = NULL;
    char item[BUFFER_SIZE] = {0};

    if (!server || !client || !player)
        return;
    if (!extract_drop_item_name(client, item, sizeof(item)))
        return;
    event = malloc(sizeof(game_event_t));
    if (!event)
        return;
    event->type = GAME_EVENT_PLAYER_DROP_ITEM;
    event->data.player_item.client_fd = client->fd;
    event->data.player_item.player_id = player->id;
    event->data.player_item.item_name = strdup(item);
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}
