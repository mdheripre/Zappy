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
    static int tick_counter = 0;

    if (!self)
        return;
    self->methods->update_players(self);
    tick_counter++;
    if (tick_counter >= 20) {
        self->methods->spawn_resources(self);
        tick_counter = 0;
    }
}
