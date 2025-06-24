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
 * @brief Consume the resources required for an incantation on the tile.
 *
 * Subtracts resources from the tile based on the incantation rule and
 * emits a tile update event.
 *
 * @param game Pointer to the game instance.
 * @param inc Pointer to the incantation containing position and level.
 */
static void consume_resources(game_t *game, incantation_t *inc)
{
    const incantation_rule_t *rule = &INCANTATION_RULES[inc->target_level - 2];
    tile_t *tile = &game->map[inc->y][inc->x];

    for (int i = 0; i < RESOURCE_COUNT; i++)
        tile->resources[i] -= rule->resources[i];
    add_tile_update_event(game, inc->x, inc->y);
}

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
    response->type = EVENT_RESP_END_INCANTATION;
    response->data.incantation.x = inc->x;
    response->data.incantation.y = inc->y;
    response->data.incantation.success = success;
    response->data.incantation.participants = inc->participants;
    return response;
}

/**
 * @brief Increments the player's level and updates the team's max level
 * count if needed.
 *
 * If the player's level reaches 6 after incrementing, the team's
 * max_level_players counter is increased.
 *
 * @param game Pointer to the game structure.
 * @param player Pointer to the player whose level is to be incremented.
 */
static void increment_player_level_and_team(game_t *game, player_t *player)
{
    team_info_t *team;

    if (!player)
        return;
    player->level++;
    if (player->level == 6) {
        team = find_team(game, player->team_name);
        if (team)
            team->max_level_players++;
    }
}

/**
 * @brief Updates the level of all players in the given participants list.
 *
 * Iterates through the participants list and increments the level
 * of each player, updating their team as needed.
 *
 * @param game Pointer to the game structure.
 * @param participants List of players to update.
 */
static void update_participants_level(game_t *game, list_t *participants)
{
    player_t *player = NULL;

    if (!participants)
        return;
    for (list_node_t *n = participants->head; n; n = n->next) {
        player = n->data;
        increment_player_level_and_team(game, player);
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
    if (success && inc.participants) {
        consume_resources(game, &inc);
        update_participants_level(game, inc.participants);
    }
    if (response)
        game->server_event_queue->methods->push_back(game->server_event_queue,
            response);
}
