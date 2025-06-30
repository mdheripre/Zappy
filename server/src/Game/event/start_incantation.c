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
    response->type = EVENT_RESP_START_INCANTATION;
    response->data.incantation.x = starter->x;
    response->data.incantation.y = starter->y;
    response->data.incantation.success = success;
    response->data.incantation.participants = inc->participants;
    game->server_event_queue->methods->push_back(game->server_event_queue,
        response);
}

/**
 * @brief Validates and gathers players eligible to participate in an
 * incantation.
 *
 * Checks all alive players at the same position and level as the starter,
 * collects them into a list, and verifies if the required number of
 * participants is met.
 *
 * @param game Pointer to the game state.
 * @param starter Pointer to the player initiating the incantation.
 * @param rule Pointer to the incantation rule specifying requirements.
 * @param out_participants Output pointer to the list of gathere
 *  participants.
 * @return true if requirements are met and participants gathered
 * false otherwise.
 */
static bool validate_and_gather_participants(game_t *game, player_t *starter,
    const incantation_rule_t *rule, list_t **out_participants)
{
    list_t *participants = NEW(list, NULL);
    player_t *p;

    if (!participants)
        return false;
    for (list_node_t *node = game->players->head; node; node = node->next) {
        p = node->data;
        if (!p || !p->is_alive || p->level != starter->level)
            continue;
        if (p->x == starter->x && p->y == starter->y)
            participants->methods->push_back(participants, p);
    }
    if (participants->size < rule->players) {
        participants->methods->destroy(participants);
        return false;
    }
    *out_participants = participants;
    return true;
}

/**
 * @brief Creates and initializes an incantation_t structure.
 *
 * @param starter Pointer to the player initiating the incantation.
 * @param target_level The level to reach after the incantation.
 * @param participants List of players participating in the incantation.
 * @return Pointer to the newly created incantation_t, or NULL on failure.
 */
static incantation_t *create_incantation_struct(player_t *starter,
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
 * @brief Prepares an incantation by validating participants and creating the
 * incantation structure.
 *
 * @param game Pointer to the current game state.
 * @param starter Pointer to the player initiating the incantation.
 * @param rule Pointer to the incantation rule to be applied.
 * @return Pointer to the created incantation_t structure, or NULL on failure.
 */
static incantation_t *prepare_incantation(game_t *game, player_t *starter,
    const incantation_rule_t *rule)
{
    int target_level = starter->level + 1;
    list_t *participants = NULL;
    incantation_t *inc = NULL;

    if (!validate_and_gather_participants(game, starter, rule, &participants))
        return NULL;
    inc = create_incantation_struct(starter, target_level, participants);
    if (!inc) {
        participants->methods->destroy(participants);
        return NULL;
    }
    return inc;
}

/**
 * @brief Handles the start of an incantation event in the game.
 *
 * This function prepares and validates an incantation attempt by a player.
 * If the incantation is valid, it is added to the game's incantation list
 * and a success response is sent. Otherwise, a failure response is sent.
 *
 * @param ctx Pointer to the game context (game_t).
 * @param data Pointer to the event data (game_event_t).
 */
void on_start_incantation(void *ctx, void *data)
{
    game_t *game = ctx;
    game_event_t *event = data;
    player_t *starter = event->data.generic_response.client->player;
    const incantation_rule_t *rule = NULL;
    incantation_t *inc = NULL;

    if (!game || !starter)
        return;
    rule = &INCANTATION_RULES[starter->level - 1];
    inc = prepare_incantation(game, starter, rule);
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
