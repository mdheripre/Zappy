/*
** EPITECH PROJECT, 2025
** server
** File description:
** has_finished
*/

#include "server.h"
#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Check if the game has reached a winning condition or overflow.
 *
 * A team wins if it has at least 6 players at the maximum level.
 * Also ends the game if the tick counter overflows.
 *
 * @param self Pointer to the game instance.
 * @return true if the game is finished, false otherwise.
 */
bool has_finished(game_t *self)
{
    team_info_t *team;

    for (list_node_t *node = self->teams->head; node; node = node->next) {
        team = node->data;
        if (team && team->max_level_players >= 6)
            return true;
    }
    if (self->tick_counter >= ULONG_MAX) {
        console_log(LOG_ERROR, "Tick counter overflow");
        return true;
    }
    return false;
}
