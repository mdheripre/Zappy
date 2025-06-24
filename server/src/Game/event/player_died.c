/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_died
*/

#include "game.h"
#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                             EVENT INGAME                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Handle player death event and queue a response.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the death event (game_event_t *).
 */
void on_player_died(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *player = NULL;
    game_event_t *response = NULL;

    if (!game || !event)
        return;
    player = event->data.player_died.player;
    if (!player)
        return;
    player->is_alive = false;
    response = malloc(sizeof(game_event_t));
    if (!response)
        return;
    response->type = EVENT_RESP_PLAYER_DIED;
    response->data.player_died.player = player;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}
