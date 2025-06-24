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

bool dispatcher_register_event(dispatcher_t *self, int index,
    event_callback_t callback, void *ctx)
{
    if (!self || index < 0 || index >= MAX_EVENT_HANDLERS)
        return false;
    self->handlers[index].callback = callback;
    self->handlers[index].ctx = ctx;
    return true;
}
