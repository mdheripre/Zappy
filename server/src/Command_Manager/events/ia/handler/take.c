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
#include "server.h"
#include "utils.h"
#include "player.h"

static const char *RESOURCE_NAMES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

static bool extract_take_item_name(client_t *client, char *item,
    size_t item_size)
{
    if (!client || !client->commands)
        return false;
    return extract_command_arguments(
        client->commands->methods->front(client->commands), item, item_size);
}

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
    event->type = GAME_EVENT_PLAYER_TAKE_ITEM;
    event->data.player_item.client_fd = client->fd;
    event->data.player_item.player_id = player->id;
    event->data.player_item.type_item = type;
    event->data.player_item.success = false;
    *event_out = event;
    return true;
}

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
