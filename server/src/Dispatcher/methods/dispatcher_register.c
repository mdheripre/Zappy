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
 * @brief Registers an event handler in the dispatcher.
 *
 * @param self Pointer to the dispatcher instance.
 * @param event Name of the event to handle.
 * @param callback Function to call when the event occurs.
 * @param ctx User-defined context passed to the callback.
 * @return true on success, false if registration failed.
 */
bool dispatcher_register(dispatcher_t *self,
    const char *event, event_callback_t callback, void *ctx)
{
    if (!self || self->count >= MAX_EVENT_HANDLERS)
        return false;
    self->handlers[self->count].event_name = event;
    self->handlers[self->count].callback = callback;
    self->handlers[self->count].ctx = ctx;
    self->count++;
    return true;
}
