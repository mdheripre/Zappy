/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** end_incantation
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
 * @brief Prepare and validate an incantation from an event.
 *
 * @param game Pointer to the game instance.
 * @param inc Output incantation structure.
 * @param event Input game event with incantation data.
 * @return true if the incantation is valid, false otherwise.
 */
static bool process_incantation(game_t *game, incantation_t *inc,
    game_event_t *event)
{
    if (!game || !event)
        return false;
    inc->x = event->data.incantation.x;
    inc->y = event->data.incantation.y;
    inc->participants = event->data.incantation.participants;
    inc->target_level = ((player_t *)
        event->data.incantation.participants->head->data)->level + 1;
    return check_incantate(game, inc);
}

/**
 * @brief Create a response event for an incantation result.
 *
 * @param inc Pointer to the incantation.
 * @param success Whether the incantation succeeded.
 * @return Pointer to the response event, or NULL on error.
 */
static game_event_t *create_incantation_response(incantation_t *inc,
    bool success)
{
    game_event_t *response = malloc(sizeof(game_event_t));

    if (!response)
        return NULL;
    response->type = GAME_EVENT_RESPONSE_END_INCANTATION;
    response->data.incantation.x = inc->x;
    response->data.incantation.y = inc->y;
    response->data.incantation.success = success;
    response->data.incantation.participants = inc->participants;
    return response;
}

/**
 * @brief Increase the level of all incantation participants.
 *
 * @param participants List of players in the incantation.
 */
static void update_participants_level(list_t *participants)
{
    player_t *p;

    if (!participants)
        return;
    for (list_node_t *n = participants->head; n; n = n->next) {
        p = n->data;
        if (p)
            p->level++;
    }
}

/**
 * @brief Handle the end of an incantation.
 *
 * Validates the result and updates levels if successful.
 *
 * @param ctx Pointer to the game instance.
 * @param data Pointer to the end-incantation event.
 */
void on_end_incantation(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    incantation_t inc;
    bool success;
    game_event_t *response = NULL;

    success = process_incantation(game, &inc, event);
    response = create_incantation_response(&inc, success);
    if (success && inc.participants)
        update_participants_level(inc.participants);
    if (response)
        game->server_event_queue->methods->push_back(game->server_event_queue,
            response);
}
