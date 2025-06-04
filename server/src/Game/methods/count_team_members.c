/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** count_team_members
*/

#include "game.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Counts how many players belong to a given team.
 *
 * Iterates through the list of players and counts how many are members
 * of the specified team.
 *
 * @param game Pointer to the game instance.
 * @param team_name Name of the team to match.
 * @return Number of players in the given team.
 */
int count_team_members(game_t *game, const char *team_name)
{
    int count = 0;
    list_node_t *node = game->players->head;
    player_t *player = NULL;

    while (node) {
        player = node->data;
        if (player && strcmp(player->team_name, team_name) == 0)
            count++;
        node = node->next;
    }
    return count;
}
