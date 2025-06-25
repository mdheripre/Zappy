/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher_register
*/

#include "dispatcher.h"

/****************************************************************************/
/*                                                                          */
/*                            PUBLIC METHODS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Registers an event handler callback at the specified index.
 *
 * @param self Pointer to the dispatcher instance.
 * @param index Index at which to register the event handler.
 * @param callback Function pointer to the event callback.
 * @param ctx Context pointer to be passed to the callback.
 * @return true on success, false on failure (invalid parameters).
 */
bool dispatcher_register_event(dispatcher_t *self, int index,
    event_callback_t callback, void *ctx)
{
    if (!self || index < 0 || index >= MAX_EVENT_HANDLERS)
        return false;
    self->handlers[index].callback = callback;
    self->handlers[index].ctx = ctx;
    return true;
}
