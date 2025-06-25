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
 * @brief Emits an event by invoking the corresponding event handler.
 *
 * If the handler for the given index exists, its callback is called with
 * the provided data. If the handler does not exist and an on_not_found
 * callback is set, it is called instead.
 *
 * @param self Pointer to the dispatcher instance.
 * @param index Index of the event handler to invoke.
 * @param data Pointer to data to pass to the event handler.
 */
void dispatcher_emit(dispatcher_t *self, int index, void *data)
{
    event_handler_t *handler = NULL;
    char *name = NULL;

    if (!self)
        return;
    if (index < 0 || index >= MAX_EVENT_HANDLERS ||
        !self->handlers[index].callback) {
        if (self->on_not_found && self->map) {
            name = (char *)event_type_name(index, self->map, self->map_size);
            self->on_not_found(self, name, data);
        }
        return;
    }
    handler = &self->handlers[index];
    handler->callback(handler->ctx, data);
}
