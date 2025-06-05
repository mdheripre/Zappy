/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_pop_front
*/

#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Removes and returns the first element from the list.
 *
 * @param self Pointer to the list.
 * @return Pointer to the data of the removed node, or NULL if the list is
 * empty.
 */
void *list_pop_front(list_t *self)
{
    list_node_t *node;
    void *data;

    if (!self || !self->head)
        return NULL;
    node = self->head;
    data = node->data;
    self->head = node->next;
    if (!self->head)
        self->tail = NULL;
    free(node);
    self->size--;
    return data;
}
