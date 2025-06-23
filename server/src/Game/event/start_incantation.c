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


static const incantation_rule_t INCANTATION_RULES[] = {
    {1, {0, 1, 0, 0, 0, 0, 0}},  // 1 -> 2
    {2, {0, 1, 1, 1, 0, 0, 0}},  // 2 -> 3
    {2, {0, 2, 0, 1, 0, 2, 0}},  // 3 -> 4
    {4, {0, 1, 1, 2, 0, 1, 0}},  // 4 -> 5
    {4, {0, 1, 2, 1, 3, 0, 0}},  // 5 -> 6
    {6, {0, 1, 2, 3, 0, 1, 0}},  // 6 -> 7
    {6, {0, 2, 2, 2, 2, 2, 1}},  // 7 -> 8
};

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
 * @brief Collect all eligible players on the tile for an incantation.
 *
 * Starts with the initiator and adds other players with same level and
 * position.
 *
 * @param game Pointer to the game instance.
 * @param starter Pointer to the player starting the incantation.
 * @param rule Pointer to the incantation rule (defines required participants).
 * @return List of participants, or NULL on allocation failure.
 */
static list_t *gather_incantation_participants(game_t *game,
    player_t *starter, const incantation_rule_t *rule)
{
    list_t *participants = NEW(list, NULL);
    list_node_t *node = NULL;
    player_t *p = NULL;

    if (!participants)
        return NULL;
    participants->methods->push_back(participants, starter);
    for (node = game->players->head; node && participants->size <
            rule->players; node = node->next) {
        p = node->data;
        if (!p || p == starter || !p->is_alive)
            continue;
        if (p->x == starter->x && p->y == starter->y &&
            p->level == starter->level)
            participants->methods->push_back(participants, p);
    }
    return participants;
}

/**
 * @brief Allocate and initialize a new incantation structure.
 *
 * @param starter Pointer to the player initiating the incantation.
 * @param target_level The level players will reach upon success.
 * @param participants List of players involved in the ritual.
 * @return Pointer to the new incantation, or NULL on failure.
 */
static incantation_t *alloc_incantation(player_t *starter,
    int target_level, list_t *participants)
{
    incantation_t *inc = malloc(sizeof(incantation_t));

    if (!inc)
        return NULL;
    inc->x = starter->x;
    inc->y = starter->y;
    inc->target_level = target_level;
    inc->tick_remaining = 300;
    inc->participants = participants;
    return inc;
}

/**
 * @brief Create a new incantation from a starter player if conditions are met.
 *
 * Validates level, gathers participants, and allocates the incantation.
 *
 * @param game Pointer to the game instance.
 * @param starter Pointer to the initiating player.
 * @return Pointer to the created incantation, or NULL if conditions fail.
 */
static incantation_t *create_incantation(game_t *game, player_t *starter)
{
    const incantation_rule_t *rule = NULL;
    list_t *participants = NULL;
    incantation_t *inc = NULL;

    if (!game || !starter || starter->level < 1 || starter->level > 7)
        return NULL;
    rule = &INCANTATION_RULES[starter->level - 1];
    participants = gather_incantation_participants(game, starter, rule);
    if (!participants || participants->size < rule->players) {
        if (participants)
            participants->methods->destroy(participants);
        return NULL;
    }
    inc = alloc_incantation(starter, starter->level + 1, participants);
    if (!inc) {
        participants->methods->destroy(participants);
        return NULL;
    }
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
    player_t *starter = event->data.generic_response.client->player;
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
