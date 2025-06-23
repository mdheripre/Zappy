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
