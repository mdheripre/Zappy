/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** list_push_front.c
*/

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

#include "list.h"

/**
 * @brief Adds a new element to the front of the list.
 *
 * Allocates a new node, assigns the provided data, and prepends it to the
 * head of the list.
 *
 * @param self Pointer to the list.
 * @param data Pointer to the data to be added.
 */
void list_push_front(list_t *self, void *data)
{
    list_node_t *node = malloc(sizeof(list_node_t));

    if (!node)
        return;
    node->data = data;
    node->next = self->head;
    self->head = node;
    if (!self->tail)
        self->tail = node;
    self->size++;
}
