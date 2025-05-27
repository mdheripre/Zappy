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
 * @brief Emits an event to all registered handlers matching the event name.
 *
 * Calls the callback functions of handlers whose event name matches the given
 * event. If no handler is found and an on_not_found callback is set,
 * it is called instead.
 *
 * @param self Pointer to the dispatcher instance.
 * @param event Name of the event to emit.
 * @param data Pointer to data to pass to the handler callbacks.
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
    if (!found && self->on_not_found)
        self->on_not_found(self, event, data);
}
