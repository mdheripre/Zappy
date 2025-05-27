/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher_emit
*/

#include "dispatcher.h"

void dispatcher_emit(dispatcher_t *self, const char *event, void *data)
{
    if (!self || !event)
        return;
    for (int i = 0; i < self->count; i++) {
        if (strcmp(self->handlers[i].event_name, event) == 0)
            self->handlers[i].callback(self->handlers[i].ctx, data);
    }
}
