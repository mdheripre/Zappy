/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_size
*/

#include "list.h"


/**
 * @brief Returns the number of elements in the list.
 *
 * @param self Pointer to the list.
 * @return Size of the list, or 0 if the list is NULL.
 */
int list_size(const list_t *self)
{
    return self ? self->size : 0;
}
