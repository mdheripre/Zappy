/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_tick
*/


#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Advances the game logic based on elapsed time.
 *
 * Compares the current time with the last tick and, if the interval
 * exceeds the tick duration, calls the game's update method.
 *
 * @param self Pointer to the game instance.
 * @param current_time Current timestamp in milliseconds.
 */
void game_tick(game_t *self, long current_time)
{
    long elapsed = current_time - self->last_tick_time;
    long tick_duration = (long)(1000.0 / self->frequency);

    if (elapsed >= tick_duration) {
        self->last_tick_time = current_time;
        self->methods->update(self);
    }
}
