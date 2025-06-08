/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** list_consume
*/

#include "list.h"

static void *is_matching(list_t *self, list_node_t *curr, list_node_t *prev)
{
    void *result = curr->data;

    if (prev)
        prev->next = curr->next;
    else
        self->head = curr->next;
    if (curr == self->tail)
        self->tail = prev;
    self->size--;
    free(curr);
    return result;
}

void *list_consume(list_t *self, bool (*match)(void *, void *), void *data)
{
    list_node_t *prev = NULL;
    list_node_t *curr = NULL;

    if (!self || !match)
        return NULL;
    curr = self->head;
    while (curr) {
        if (match(curr->data, data))
            return is_matching(self, curr, prev);
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}
