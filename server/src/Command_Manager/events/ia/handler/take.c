/*
** EPITECH PROJECT, 2025
** server
** File description:
** take
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
 * @brief Extract the item name from a "Take" command.
 *
 * @param client Pointer to the client issuing the command.
 * @param item Output buffer to store the extracted item name.
 * @param item_size Size of the output buffer.
 * @return true on success, false on failure.
 */
static bool extract_take_item_name(client_t *client, char *item,
    size_t item_size)
{
    if (!client || !client->commands)
        return false;
    return extract_command_arguments(
        client->commands->methods->front(client->commands), item, item_size);
}

/**
 * @brief Get the resource type index for the item to take.
 *
 * Sends "ko" to the client if the item is invalid.
 *
 * @param client Pointer to the client.
 * @return Resource index on success, -1 on failure.
 */
static int get_take_item_type(client_t *client)
{
    char item[BUFFER_SIZE] = {0};
    int type = -1;

    if (!extract_take_item_name(client, item, sizeof(item))) {
        dprintf(client->fd, "ko\n");
        return -1;
    }
    type = resource_from_string(item);
    if (type < 0 || type >= RESOURCE_COUNT) {
        dprintf(client->fd, "ko\n");
        return -1;
    }
    return type;
}

/**
 * @brief Prepare a take item event for a given client.
 *
 * Validates the item and fills the event with necessary data.
 *
 * @param server Pointer to the server.
 * @param client Pointer to the client.
 * @param event_out Output pointer to the created event.
 * @return true on success, false otherwise.
 */
static bool prepare_take_event(server_t *server, client_t *client,
    game_event_t **event_out)
{
    player_t *player = client ? client->player : NULL;
    int type = -1;
    game_event_t *event = NULL;

    if (!server || !client || !player)
        return false;
    type = get_take_item_type(client);
    if (type < 0)
        return false;
    event = calloc(1, sizeof(game_event_t));
    if (!event)
        return false;
    event->type = EVENT_PLAYER_TAKE_ITEM;
    event->data.player_item.player = player;
    event->data.player_item.type_item = type;
    event->data.player_item.success = false;
    *event_out = event;
    return true;
}

/**
 * @brief Handle the "Take" command from a client.
 *
 * Prepares and queues a take event for processing.
 *
 * @param ctx Pointer to the server instance.
 * @param data Pointer to the client.
 */
void handle_command_take(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    game_event_t *event = NULL;

    if (!prepare_take_event(server, client, &event))
        return;
    server->game->event_queue->methods->push_back(
        server->game->event_queue, event);
}
