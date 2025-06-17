/*
** EPITECH PROJECT, 2025
** server
** File description:
** drop
*/

#include "game.h"
#include "server.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief String names for each resource type, indexed by enum.
 */
static const char *RESOURCE_NAMES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

/**
 * @brief Convert a resource name string to its corresponding enum index.
 *
 * @param name Resource name string (e.g., "food").
 * @return Index of the resource, or -1 if not found.
 */
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

/**
 * @brief Emit a tile update event for GUI after a resource change.
 *
 * @param game Pointer to the game instance.
 * @param x X coordinate of the tile.
 * @param y Y coordinate of the tile.
 */
void emit_tile_update(game_t *game, int x, int y)
{
    game_event_t *evt = malloc(sizeof(game_event_t));

    if (!evt)
        return;
    memset(evt, 0, sizeof(game_event_t));
    evt->type = GAME_EVENT_RESPONSE_TILE_UPDATED;
    evt->data.tile.x = x;
    evt->data.tile.y = y;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        evt);
}

/**
 * @brief Send a response to the client after a drop command.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player.
 * @param client_fd File descriptor of the client.
 * @param msg Response message ("ok\n" or "ko\n").
 */
static void send_drop_response(game_t *game, player_t *player,
    int client_fd, const char *msg)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return;
    memset(response, 0, sizeof(game_event_t));
    response->type = GAME_EVENT_RESPONSE_DROP;
    response->data.generic_response.player_id = player->id;
    response->data.generic_response.client_fd = client_fd;
    response->data.generic_response.response = strdup(msg);
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
}

/**
 * @brief Handle a drop command from a player.
 *
 * Updates the tile and player's inventory if valid, and sends a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the drop event.
 */
void on_drop(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    int type = resource_from_string(event->data.player_item.item_name);
    player_t *p = find_player_by_id(game, event->data.player_item.player_id);

    free(event->data.player_item.item_name);
    if (!game || !event || !p || type < 0 || type >= RESOURCE_COUNT)
        return send_drop_response(game, p, event->data.player_item.client_fd,
            "ko\n");
    if (p->inventory[type] <= 0)
        return send_drop_response(game, p, event->data.player_item.client_fd,
            "ko\n");
    player_remove_resource(p, type, 1);
    game->map[p->y][p->x].resources[type]++;
    send_drop_response(game, p, event->data.player_item.client_fd,
        "ok\n");
    emit_tile_update(game, p->x, p->y);
}
