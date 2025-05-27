/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher_create
*/

#include "dispatcher.h"


static const dispatcher_methods_t DISPATCHER_VTABLE = {
    .register_event = dispatcher_register,
    .emit = dispatcher_emit
};


dispatcher_t *dispatcher_create(void)
{
    dispatcher_t *dispatcher = malloc(sizeof(dispatcher_t));

    if (!dispatcher)
        return NULL;
    memset(dispatcher, 0, sizeof(dispatcher_t));
    dispatcher->vtable = &DISPATCHER_VTABLE;
    return dispatcher;
}
