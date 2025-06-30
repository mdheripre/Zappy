/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** check_incantate
*/

#include "game.h"
#include "utils.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                         INCANTATION RULES                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Rules defining resources and players required for each level up.
 *
 * Each entry corresponds to a level-up requirement from level N to N+1.
 */
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
 * @brief Human-readable names for each resource type.
 *
 * Indexed by the corresponding resource enum.
 */
static const char *RESOURCE_NAMES[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

/**
 * @brief Check if enough players are eligible for the incantation.
 *
 * @param inc Pointer to the incantation info.
 * @param rule Pointer to the incantation rule.
 * @return true if enough valid players are present, false otherwise.
 */
static bool check_incantate_players(const incantation_t *inc,
    const incantation_rule_t *rule)
{
    int count = 0;
    player_t *p;

    for (list_node_t *node = inc->participants->head; node;
        node = node->next) {
        p = (player_t *)node->data;
        if (p && p->is_alive && p->x == inc->x && p->y == inc->y &&
            p->level == inc->target_level - 1)
            count++;
    }
    return count >= rule->players;
}

/**
 * @brief Check if a tile has all the resources required for an incantation.
 *
 * Logs the required and available resources and validates sufficiency.
 *
 * @param tile Pointer to the tile being checked.
 * @param rule Pointer to the incantation rule containing requirements.
 * @return true if all required resources are present, false otherwise.
 */
static bool check_incantate_resources(const tile_t *tile,
    const incantation_rule_t *rule)
{
    int available = 0;
    int required = 0;

    for (int r = 0; r < RESOURCE_COUNT; r++) {
        available = tile->resources[r];
        required = rule->resources[r];
        if (required > 0) {
            console_log(LOG_INFO,
                "Resource check: need %d x %s, found %d",
                required, RESOURCE_NAMES[r], available);
        }
        if (available < required) {
            console_log(LOG_WARNING,
                "Insufficient %s: required %d, available %d",
                RESOURCE_NAMES[r], required, available);
            return false;
        }
    }
    console_log(LOG_SUCCESS, "All required resources are present.");
    return true;
}

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Validate an incantation based on rules and current state.
 *
 * @param game Pointer to the game state.
 * @param inc Pointer to the incantation data.
 * @return true if incantation is valid, false otherwise.
 */
bool check_incantate(game_t *game, incantation_t *inc)
{
    const incantation_rule_t *rule = NULL;
    tile_t *tile = NULL;

    if (!game || !inc || !inc->participants)
        return false;
    if (inc->target_level < 2 || inc->target_level > 8)
        return false;
    rule = &INCANTATION_RULES[inc->target_level - 2];
    tile = &game->map[inc->y][inc->x];
    if (!check_incantate_players(inc, rule))
        return false;
    if (!check_incantate_resources(tile, rule))
        return false;
    return true;
}
