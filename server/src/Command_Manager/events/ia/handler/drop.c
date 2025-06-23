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


static const char *RESOURCE_NAMES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

int resource_from_string(const char *name)
{
    if (!name)
        return -1;
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        if (strcmp(name, RESOURCE_NAMES[i]) == 0)
            return i;
    }
    return -1;
}

static bool extract_drop_item_name(client_t *client, char *item,
    size_t item_size)
{
    if (!client || !client->commands)
        return false;
    return extract_command_arguments(
        client->commands->methods->front(client->commands), item, item_size);
}

static bool validate_and_get_drop_type(server_t *server, client_t *client,
    int *type_out)
{
    player_t *player = client ? client->player : NULL;
    char item[BUFFER_SIZE] = {0};
    int type = -1;

    if (!server || !client || !player)
        return false;
    if (!extract_drop_item_name(client, item, sizeof(item))) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    type = resource_from_string(item);
    if (type < 0 || type >= RESOURCE_COUNT) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    *type_out = type;
    return true;
}

static bool prepare_drop_event(server_t *server, client_t *client,
    game_event_t **event_out)
{
    int type = -1;
    game_event_t *event;

    if (!validate_and_get_drop_type(server, client, &type))
        return false;
    event = calloc(1, sizeof(game_event_t));
    if (!event)
        return false;
    event->type = GAME_EVENT_PLAYER_DROP_ITEM;
    event->data.player_item.player = client->player;
    event->data.player_item.type_item = type;
    event->data.player_item.success = false;
    *event_out = event;
    return true;
}

void handle_command_drop(void *ctx, void *data)
{
    server_t *server = (server_t *)ctx;
    client_t *client = (client_t *)data;
    game_event_t *event = NULL;

    if (!prepare_drop_event(server, client, &event))
        return;
    server->game->event_queue->methods->push_back(
        server->game->event_queue, event);
}
