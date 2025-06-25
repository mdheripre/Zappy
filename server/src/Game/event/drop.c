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
 * Emits a tile update event into the server event queue.
 *
 * Creates a EVENT_RESP_TILE_UPDATED event and pushes it into the
 * server-side queue to signal that a tile's content has changed.
 *
 * @param game Pointer to the game instance.
 * @param x X coordinate of the tile to update.
 * @param y Y coordinate of the tile to update.
 */
void emit_tile_update(game_t *game, int x, int y)
{
    game_event_t *evt = calloc(1, sizeof(game_event_t));

    if (!evt)
        return;
    evt->type = EVENT_RESP_TILE_UPDATED;
    evt->data.tile.x = x;
    evt->data.tile.y = y;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        evt);
}

/**
 * Sends a drop result event to the server event queue.
 *
 * Generates a EVENT_RESP_DROP event with the result of a drop
 * action and pushes it to the server queue for processing.
 *
 * @param game Pointer to the game instance.
 * @param player The player who attempted the drop.
 * @param event The original drop event with item info.
 * @param success Whether the drop action succeeded.
 */
void send_drop_response(game_t *game, player_t *player,
    game_event_t *event, bool success)
{
    game_event_t *response = calloc(1, sizeof(game_event_t));

    if (!response)
        return;
    response->type = EVENT_RESP_DROP;
    response->data.player_item.player = player;
    response->data.player_item.type_item = event->data.player_item.type_item;
    response->data.player_item.success = success;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
}

/**
 * Handles the drop action for a player.
 *
 * Verifies inventory and tile state, updates the map and inventory,
 * and emits appropriate response and tile update events.
 *
 * @param ctx Pointer to the game instance (game_t *).
 * @param data Pointer to the drop event (game_event_t *).
 */
void on_drop(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *p = event->data.player_item.player;
    int type = event->data.player_item.type_item;

    if (!game || !event || !p || type < 0 || type >= RESOURCE_COUNT)
        return send_drop_response(game, p, event, false);
    if (p->inventory[type] <= 0)
        return send_drop_response(game, p, event, false);
    player_remove_resource(p, type, 1);
    game->map[p->y][p->x].resources[type]++;
    send_drop_response(game, p, event, true);
    emit_tile_update(game, p->x, p->y);
}
