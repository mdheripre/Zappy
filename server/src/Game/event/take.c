/*
** EPITECH PROJECT, 2025
** server
** File description:
** take
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
 * @brief Send response for a 'Take' command (ok/ko).
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player.
 * @param event Original event with item info.
 * @param success True if take succeeded, false otherwise.
 */
void send_take_response(game_t *game, player_t *player,
    game_event_t *event, bool success)
{
    game_event_t *response = calloc(1, sizeof(game_event_t));

    if (!response)
        return;
    response->type = EVENT_RESP_TAKE;
    response->data.player_item.player = player;
    response->data.player_item.type_item = event->data.player_item.type_item;
    response->data.player_item.success = success;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
}

/**
 * @brief Handle a player 'Take' command on a tile.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the game_event_t with player and item type.
 */
void on_take(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *p = event->data.player_item.player;
    int type = event->data.player_item.type_item;

    if (!game || !event || !p || type < 0 || type >= RESOURCE_COUNT)
        return send_take_response(game, p, event, false);
    if (game->map[p->y][p->x].resources[type] <= 0)
        return send_take_response(game, p, event, false);
    game->map[p->y][p->x].resources[type]--;
    player_add_resource(p, type, 1);
    send_take_response(game, p, event, true);
    emit_tile_update(game, p->x, p->y);
}
