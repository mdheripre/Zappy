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
 * @brief Gets the name of an event type.
 *
 * Searches the EVENT_TYPE_MAP array for the given type and returns its
 * associated name. Returns "UNKNOWN" if the type is not found.
 *
 * @param type The event type to resolve.
 * @return String name of the event type, or "UNKNOWN".
 */
const char *event_type_name(game_event_type_t type)
{
    for (size_t i = 0;
        i < sizeof(EVENT_TYPE_MAP) / sizeof(EVENT_TYPE_MAP[0]); i++) {
        if (EVENT_TYPE_MAP[i].type == type)
            return EVENT_TYPE_MAP[i].name;
    }
    return "UNKNOWN";
}

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
    const char *event_name = NULL;

    if (!self || !self->dispatcher)
        return;
    event = self->methods->pop_event(self);
    while (event) {
        event_name = event_type_name(event->type);
        EMIT(self->dispatcher, event_name, event);
        free(event);
        event = self->methods->pop_event(self);
    }
}
