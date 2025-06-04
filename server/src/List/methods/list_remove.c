/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_remove
*/

#include "list.h"

static void remove_node(list_t *self, list_node_t *node, list_node_t *prev)
{
    if (!self || !node || !prev)
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
