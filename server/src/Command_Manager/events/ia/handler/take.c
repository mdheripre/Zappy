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
 * @brief Extracts the item name from the client's command.
 *
 * @param client Pointer to the client structure.
 * @param item Buffer to store the extracted item name.
 * @param item_size Size of the item buffer.
 * @return true if extraction was successful, false otherwise.
 */
static bool extract_item_from_command(client_t *client, char *item,
    size_t item_size)
{
    if (!client || !client->commands)
        return false;
    return extract_command_arguments(
        client->commands->methods->front(client->commands), item, item_size);
}

/**
 * @brief Queues a take item event for the player.
 *
 * @param server Pointer to the server structure.
 * @param client_fd File descriptor of the client.
 * @param player_id ID of the player.
 * @param item Name of the item to take.
 */
static void queue_take_item_event(server_t *server, int client_fd,
    int player_id, const char *item)
{
    game_event_t *event = malloc(sizeof(game_event_t));

    if (!event)
        return;
    event->type = GAME_EVENT_PLAYER_TAKE_ITEM;
    event->data.player_item.client_fd = client_fd;
    event->data.player_item.player_id = player_id;
    event->data.player_item.item_name = strdup(item);
    server->game->event_queue->methods->push_back(server->game->event_queue,
        event);
}

/**
 * @brief Handles the "take" command from a client.
 *
 * @param ctx Pointer to the server context.
 * @param data Pointer to the client structure.
 */
void handle_command_take(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    player_t *player = client ? client->player : NULL;
    char item[BUFFER_SIZE] = {0};

    if (!server || !client || !player)
        return;
    if (!extract_item_from_command(client, item, sizeof(item))) {
        dprintf(client->fd, "ko\n");
        return;
    }
    queue_take_item_event(server, client->fd, player->id, item);
}
