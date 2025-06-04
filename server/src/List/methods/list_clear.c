/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_clear
*/

#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Clears all elements from the list and frees associated memory.
 *
 * Iterates through the list, freeing each node and its data using the
 * provided free function (if any). Resets the list to an empty state.
 *
 * @param self Pointer to the list to clear.
 */
void list_clear(list_t *self)
{
    list_node_t *current = self->head;
    list_node_t *next = NULL;

    while (current) {
        next = current->next;
        if (self->free_fn)
            self->free_fn(current->data);
        free(current);
        current = next;
    }
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}
