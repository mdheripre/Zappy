/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** find_team
*/

#include "server.h"
#include "player.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER GAME                                     */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Find a team by its name in the game structure.
 *
 * @param game Pointer to the game structure containing the teams list.
 * @param team_name Name of the team to search for.
 * @return Pointer to the team_info_t if found, NULL otherwise.
 */
team_info_t *find_team(game_t *game, const char *team_name)
{
    list_node_t *node = NULL;
    team_info_t *team = NULL;

    for (node = game->teams->head; node; node = node->next) {
        team = node->data;
        if (strcmp(team->team_name, team_name) == 0)
            return team;
    }
    return NULL;
}
