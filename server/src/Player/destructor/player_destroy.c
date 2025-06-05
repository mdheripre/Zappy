/*
** EPITECH PROJECT, 2025
** server
** File description:
** player_destroy
*/

#include "player.h"

/****************************************************************************/
/*                                                                          */
/*                              DESTRUCTOR                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Frees the memory used by a player.
 *
 * Frees the team name string associated with the player. Does not
 * deallocate the player struct itself.
 *
 * @param self Pointer to the player to destroy.
 */
void player_destroy(player_t *self)
{
    if (!self)
        return;
    free(self->team_name);
}
