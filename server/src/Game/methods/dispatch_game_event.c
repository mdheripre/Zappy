/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatch_game_event
*/


#include "game.h"
#include "server.h"
#include "dispatcher.h"
#include "client.h"
#include "shared.h"

/****************************************************************************/
/*                                                                          */
/*                            METHODS GAME                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Dispatches all pending game events.
 *
 * Pops all events from the game's event queue and emits them through the
 * dispatcher using their resolved name.
 *
 * @param self Pointer to the game instance.
 */
void game_dispatch_events(game_t *self)
{
    game_event_t *event = NULL;

    if (!self || !self->dispatcher)
        return;
    event = self->event_queue->methods->pop_front(self->event_queue);
    while (event) {
        EMIT(self->dispatcher, event->type, event);
        free(event);
        event = self->event_queue->methods->pop_front(self->event_queue);
    }
}
