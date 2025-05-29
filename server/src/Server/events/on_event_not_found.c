/*
** EPITECH PROJECT, 2025
** server
** File description:
** on_event_not_found
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                               EVENT GLOBAL                               */
/*                                                                          */
/****************************************************************************/

/**
 * Handles unknown or unrecognized global events.
 *
 * @param self   Pointer to the dispatcher instance (unused).
 * @param event  Name of the unknown event.
 * @param        Unused parameter.
 */
void on_event_not_found(dispatcher_t *self, const char *event, void *)
{
    (void)self;
    console_log(LOG_INFO, "Ignored unknown global event \"%s\"", event);
}
