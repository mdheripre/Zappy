/*
** EPITECH PROJECT, 2025
** server
** File description:
** game_add_event
*/

#include "game.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Adds a new event to the game's event queue.
 *
 * Makes a copy of the given event and appends it to the event queue.
 *
 * @param self Pointer to the game instance.
 * @param event Event to be added.
 */
void game_add_event(game_t *self, game_event_t event)
{
    game_event_t *copy = malloc(sizeof(game_event_t));

    if (!self || !copy)
        return;
    *copy = event;
    self->event_queue->methods->push_back(self->event_queue, copy);
}
