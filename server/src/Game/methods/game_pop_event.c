/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_pop_event
*/

#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Pops the oldest event from the game's event queue.
 *
 * Retrieves and removes the first event in the event queue.
 *
 * @param self Pointer to the game instance.
 * @return Pointer to the popped event, or NULL on error.
 */
game_event_t *game_pop_event(game_t *self)
{
    if (!self)
        return NULL;
    return (game_event_t *)
        self->event_queue->methods->pop_front(self->event_queue);
}
