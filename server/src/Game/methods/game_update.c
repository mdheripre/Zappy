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
void game_update(game_t *self, int ticks)
{
    if (!self)
        return;
    self->methods->update_players(self, ticks);
    self->methods->update_incantations(self, ticks);
    self->tick_counter_tiled += ticks;
    if (self->tick_counter_tiled >= 20) {
        self->methods->spawn_resources(self);
        self->tick_counter_tiled = 0;
    }
}
