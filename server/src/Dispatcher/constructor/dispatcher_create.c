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
    .register_event = dispatcher_register,
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
dispatcher_t *dispatcher_create(event_not_found_t default_not_found)
{
    dispatcher_t *dispatcher = malloc(sizeof(dispatcher_t));

    if (!dispatcher)
        return NULL;
    memset(dispatcher, 0, sizeof(dispatcher_t));
    dispatcher->vtable = &DISPATCHER_VTABLE;
    dispatcher->on_not_found = default_not_found;
    return dispatcher;
}
