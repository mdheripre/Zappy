/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** list_contain.c
*/

#include "list.h"
#include <stdbool.h>

/****************************************************************************/
/*                                                                          */
/*                             LIST METHODS                                 */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Checks if the list contains a given element using a comparison
 *        function.
 *
 * Iterates through the list and calls the provided `compare` function
 * on each element. If any comparison returns true, the element is
 * considered present.
 *
 * @param self Pointer to the list instance.
 * @param data Element to search for.
 * @param compare Function to compare two elements (returns true if equal).
 * @return true if the element is found, false otherwise.
 */
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
