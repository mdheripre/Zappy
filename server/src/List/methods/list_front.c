/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_front
*/

#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Get the data from the first element of the list.
 *
 * @param self Pointer to the list.
 * @return Pointer to the data, or NULL if the list is empty.
 */
void *list_peek_front(const list_t *self)
{
    if (!self || !self->head)
        return NULL;
    return self->head->data;
}
