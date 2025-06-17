/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** list_indec.c
*/

#include <stddef.h>
#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Retrieves the data at a specific index in the list.
 *
 * Traverses the list from the head to the specified index and returns
 * the data if found. If the index is out of bounds, returns NULL.
 *
 * @param self Pointer to the list instance.
 * @param index Index of the element to retrieve.
 * @return Pointer to the data at the specified index, or NULL if not found.
 */
void *list_index(const list_t *self, size_t index)
{
    list_node_t *current;

    if (!self || (int)index >= self->size - 1)
        return NULL;
    for (current = self->head; current && index > 0; --index)
        current = current->next;
    return current ? current->data : NULL;
}
