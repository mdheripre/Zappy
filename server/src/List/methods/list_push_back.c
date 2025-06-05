/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_push_back
*/


#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Adds a new element to the end of the list.
 *
 * Allocates a new node, assigns the provided data, and appends it to the
 * tail of the list.
 *
 * @param self Pointer to the list.
 * @param data Pointer to the data to be added.
 */
void list_push_back(list_t *self, void *data)
{
    list_node_t *node = malloc(sizeof(list_node_t));

    if (!node)
        return;
    node->data = data;
    node->next = NULL;
    if (!self->head)
        self->head = node;
    else
        self->tail->next = node;
    self->tail = node;
    self->size++;
}
