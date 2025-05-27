/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher_emit
*/

#include "dispatcher.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                             PUBLIC METHODS                               */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Emits an event with the given name and data to all registered
 * handlers.
 *
 * This function iterates through all registered event handlers in the
 * dispatcher and calls the callback function for each handler that
 * matches the event name. If no handler is found for the event, an
 * error message is logged.
 *
 * @param self Pointer to the dispatcher instance.
 * @param event The name of the event to emit.
 * @param data Pointer to the data to pass to the event handlers.
 */
void dispatcher_emit(dispatcher_t *self, const char *event, void *data)
{
    bool found = false;

    if (!self || !event)
        return;
    for (int i = 0; i < self->count; i++) {
        if (strcmp(self->handlers[i].event_name, event) == 0) {
            self->handlers[i].callback(
                self->handlers[i].ctx, data);
            found = true;
        }
    }
    if (!found)
        console_log(LOG_ERROR,
            "Event \"%s\" not handled by dispatcher", event);
}
