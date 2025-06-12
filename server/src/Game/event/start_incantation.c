/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** start_incantation
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
 * @brief Send a response indicating the start of an incantation.
 *
 * @param game Pointer to the game instance.
 * @param starter Pointer to the player who started the incantation.
 * @param inc Pointer to the incantation data.
 * @param success Whether the incantation was valid.
 */
static void send_incantation_response(game_t *game, player_t *starter,
    incantation_t *inc, bool success)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return;
    response->type = GAME_EVENT_RESPONSE_START_INCANTATION;
    response->data.incantation.x = starter->x;
    response->data.incantation.y = starter->y;
    response->data.incantation.success = success;
    response->data.incantation.participants = inc->participants;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}

/**
 * @brief Create a new incantation object from a starter player.
 *
 * @param game Pointer to the game instance.
 * @param starter Pointer to the player initiating the incantation.
 * @return Pointer to the created incantation, or NULL on failure.
 */
static incantation_t *create_incantation(game_t *game, player_t *starter)
{
    incantation_t *inc = malloc(sizeof(incantation_t));

    if (!inc)
        return NULL;
    inc->x = starter->x;
    inc->y = starter->y;
    inc->target_level = starter->level + 1;
    inc->tick_remaining = 300;
    inc->participants = game->methods->get_players_on_tile(
        game, inc->x, inc->y, starter->level);
    return inc;
}

/**
 * @brief Handle the start of an incantation event.
 *
 * Validates conditions and queues the incantation if valid.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the event triggering the incantation.
 */
void on_start_incantation(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *starter = find_player_by_id(game,
        event->data.generic_response.player_id);
    incantation_t *inc = NULL;

    if (!game || !starter)
        return;
    inc = create_incantation(game, starter);
    if (!inc)
        return;
    if (!check_incantate(game, inc)) {
        send_incantation_response(game, starter, inc, false);
        free(inc);
        return;
    }
    game->incantations->methods->push_back(game->incantations, inc);
    send_incantation_response(game, starter, inc, true);
}
