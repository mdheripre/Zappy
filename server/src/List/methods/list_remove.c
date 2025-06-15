/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_remove
*/

#include "list.h"

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Removes a node from the list and frees its memory.
 *
 * Unlinks the specified node from the list, updates head/tail pointers,
 * frees its content using the list's free function if available, and
 * frees the node itself.
 *
 * @param self Pointer to the list.
 * @param node Node to remove.
 * @param prev Previous node before `node` (can be NULL).
 */
static void remove_node(list_t *self, list_node_t *node, list_node_t *prev)
{
    if (!self || !node)
        return;
    if (prev)
        prev->next = node->next;
    else
        self->head = node->next;
    if (node == self->tail)
        self->tail = prev;
    if (self->free_fn)
        self->free_fn(node->data);
    free(node);
    self->size--;
    return;
}

/**
 * @brief Removes the first node in the list that matches the target pointer.
 *
 * Traverses the list and removes the node whose data pointer equals
 * `target`. Uses `remove_node` to handle memory deallocation and
 * list integrity.
 *
 * @param self Pointer to the list.
 * @param target Pointer to the data to remove.
 */
void list_remove(list_t *self, void *target)
{
    list_node_t *prev = NULL;
    list_node_t *curr = NULL;

    if (!self || !target)
        return;
    curr = self->head;
    while (curr) {
        if (curr->data == target)
            return remove_node(self, curr, prev);
        prev = curr;
        curr = curr->next;
    }
}
