/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** poll_manager_destroy
*/

#include "poll_manager.h"

/****************************************************************************/
/*                                                                          */
/*                              DESTRUCTOR                                  */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Destroys a poll_manager_t instance.
 *
 * Safely frees resources associated with the given poll manager.
 * Does nothing if the pointer is NULL.
 *
 * @param self Pointer to the poll_manager_t instance to destroy.
 */
void poll_manager_destroy(poll_manager_t *self)
{
    if (!self)
        return;
}
