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
 * @brief Allocates and initializes a new dispatcher_t instance.
 *
 * @return Pointer to the newly created dispatcher_t, or NULL on failure.
 */
dispatcher_t *dispatcher_create(void)
{
    dispatcher_t *dispatcher = malloc(sizeof(dispatcher_t));

    if (!dispatcher)
        return NULL;
    memset(dispatcher, 0, sizeof(dispatcher_t));
    dispatcher->vtable = &DISPATCHER_VTABLE;
    return dispatcher;
}
