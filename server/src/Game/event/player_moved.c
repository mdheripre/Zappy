/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_moved
*/

#include "server.h"
#include "game.h"
#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Create and queue a player movement response event.
 *
 * @param game Pointer to the game instance.
 * @param player Pointer to the moved player.
 * @param event Original move event received.
 */
static void send_player_moved_response(game_t *game, player_t *player,
    game_event_t *event)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return;
    response->type = GAME_EVENT_RESPONSE_PLAYER_MOVED;
    response->data.player_moved.player_id = player->id;
    response->data.player_moved.x = player->x;
    response->data.player_moved.y = player->y;
    response->data.player_moved.orientation = player->orientation;
    response->data.player_moved.client_fd = event->data.player_moved.client_fd;
    response->data.player_moved.ia_success = true;
    game->server_event_queue->methods->push_back(
        game->server_event_queue, response);
}

/**
 * @brief Handle player movement and send a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the move event (game_event_t *).
 */
void on_player_moved(void *ctx, void *data)
{
    game_t *game = (game_t *)ctx;
    game_event_t *event = (game_event_t *)data;
    player_t *player = NULL;

    if (!game || !event)
        return;
    player = find_player_by_id(game,
        event->data.player_moved.player_id);
    player_move(player, game->width, game->height,
        event->data.player_moved.direction);
    send_player_moved_response(game, player, event);
}
