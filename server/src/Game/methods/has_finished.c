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

bool has_finished(game_t *self)
{
    team_info_t *team;

    for (list_node_t *node = self->teams->head; node; node = node->next) {
        team = node->data;
        if (team && team->max_level_players >= 6)
            return true;
    }
    return false;
}
