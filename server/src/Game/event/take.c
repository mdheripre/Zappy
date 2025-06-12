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
 * @brief Send a response event to the client after a take command.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the player who took the resource.
 * @param client_fd File descriptor of the client.
 * @param msg Response message ("ok\n" or "ko\n").
 */
static void send_take_response(game_t *game, player_t *player,
    int client_fd, const char *msg)
{
    game_event_t *response = calloc(1, sizeof(game_event_t));

    if (!response)
        return;
    response->type = GAME_EVENT_RESPONSE_TAKE;
    response->data.generic_response.player_id = player->id;
    response->data.generic_response.client_fd = client_fd;
    response->data.generic_response.response = msg;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
}

/**
 * @brief Handle a take command from a player.
 *
 * Transfers a resource from the map to the player's inventory
 * and sends a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the take command event.
 */
void on_take(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    int type = resource_from_string(event->data.player_item.item_name);
    player_t *p = find_player_by_id(game, event->data.player_item.player_id);

    free(event->data.player_item.item_name);
    if (!game || !event || !p || type < 0 || type >= RESOURCE_COUNT)
        return send_take_response(game, p, event->data.player_item.client_fd,
            "ko\n");
    if (game->map[p->y][p->x].resources[type] <= 0)
        return send_take_response(game, p, event->data.player_item.client_fd,
            "ko\n");
    game->map[p->y][p->x].resources[type]--;
    player_add_resource(p, type, 1);
    send_take_response(game, p, event->data.player_item.client_fd, "ok\n");
    emit_tile_update(game, p->x, p->y);
}
