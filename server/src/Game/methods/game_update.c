/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_update
*/

#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Updates the state of the game.
 *
 * Placeholder function. Expected to trigger updates for players,
 * eggs, incantations, and resources in a complete implementation.
 *
 * @param self Pointer to the game instance.
 */
void game_update(game_t *self)
{
    if (!self)
        return;
    if (self->methods->update_players)
        self->methods->update_players(self);
}
