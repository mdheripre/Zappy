/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** check_incantate
*/

#include "game.h"
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
    {1, {1, 0, 0, 0, 0, 0, 0}},  // 1 -> 2
    {2, {1, 1, 1, 0, 0, 0, 0}},  // 2 -> 3
    {2, {2, 0, 1, 0, 2, 0, 0}},  // 3 -> 4
    {4, {1, 1, 2, 0, 1, 0, 0}},  // 4 -> 5
    {4, {1, 2, 1, 3, 0, 0, 0}},  // 5 -> 6
    {6, {1, 2, 3, 0, 1, 0, 0}},  // 6 -> 7
    {6, {2, 2, 2, 2, 2, 1, 0}},  // 7 -> 8
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
            p->level == inc->target_level)
            count++;
    }
    return count >= rule->players;
}

/**
 * @brief Check if the tile has required resources for the incantation.
 *
 * @param tile Pointer to the tile to check.
 * @param rule Pointer to the incantation rule.
 * @return true if all required resources are present, false otherwise.
 */
static bool check_incantate_resources(const tile_t *tile,
    const incantation_rule_t *rule)
{
    for (int r = 0; r < RESOURCE_COUNT; r++) {
        if (tile->resources[r] < rule->resources[r])
            return false;
    }
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
