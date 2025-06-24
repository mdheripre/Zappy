/*
** EPITECH PROJECT, 2025
** server
** File description:
** dispatcher_create
*/

#include "dispatcher.h"

/****************************************************************************/
/*                                                                          */
/*                               METHODS                                    */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Virtual table for dispatcher methods.
 *
 * Contains function pointers for registering events and emitting events.
 */
static const dispatcher_methods_t DISPATCHER_VTABLE = {
    .register_event = dispatcher_register_event,
    .emit = dispatcher_emit
};

/****************************************************************************/
/*                                                                          */
/*                            CONSTRUCTOR                                   */
/*                                                                          */
/****************************************************************************/



/**
 * @brief Creates and initializes a new dispatcher instance.
 *
 * Allocates memory for a dispatcher_t structure, initializes its fields to
 * zero, sets up the vtable, and assigns the default event-not-found handler.
 *
 * @param default_not_found Function pointer to handle events not found.
 * @return Pointer to the newly created dispatcher_t, or NULL on allocation
 * failure.
 */
dispatcher_t *dispatcher_create(event_not_found_t default_not_found,
    const event_type_map_entry_t *map, size_t map_size)
{
    dispatcher_t *self = malloc(sizeof(dispatcher_t));

    if (!self)
        return NULL;
    memset(self->handlers, 0, sizeof(self->handlers));
    self->on_not_found = default_not_found;
    self->map = map;
    self->map_size = map_size;
    self->vtable = &DISPATCHER_VTABLE;
    return self;
}
