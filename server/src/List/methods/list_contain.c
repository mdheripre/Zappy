/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** list_contain.c
*/

#include "list.h"
#include <stdbool.h>

bool list_contain(list_t *self, void *data, bool (*compare)(void *, void *))
{
    if (!self || !data || !compare)
        return false;
    for (list_node_t *current = self->head; current != NULL;
        current = current->next) {
        if (compare(current->data, data))
            return true;
    }
    return false;
}
