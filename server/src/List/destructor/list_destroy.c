/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_destroy
*/

#include "list.h"


/**
 * @brief Destroys the given list and frees its resources.
 *
 * Calls the clear method of the list to remove all elements.
 *
 * @param self Pointer to the list to be destroyed.
 */
void list_destroy(list_t *self)
{
    if (!self)
        return;
    self->methods->clear(self);
}
