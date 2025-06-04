/*
** EPITECH PROJECT, 2025
** server
** File description:
** list_create
*/

#include "list.h"

/**
 * @brief Static constant structure holding method pointers for list
 * operations.
 *
 * This structure initializes the function pointers for common list operations
 * such as destroy, clear, push_back, pop_front, and size.
 */
static const list_methods_t LIST_METHODS = {
    .destroy = list_destroy,
    .clear = list_clear,
    .push_back = list_push_back,
    .pop_front = list_pop_front,
    .size = list_size,
    .contain = list_contain,
    .remove = list_remove
};

/**
 * @brief Creates a new list instance.
 *
 * Allocates and initializes a new list structure. The list will use the
 * provided free function to deallocate node data, or the standard free()
 * if none is given.
 *
 * @param free_fn Function pointer to free node data, or NULL to use default
 *                free().
 * @return Pointer to the newly created list, or NULL on allocation failure.
 */
list_t *list_create(void (*free_fn)(void *))
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->free_fn = free_fn ? free_fn : free;
    list->methods = &LIST_METHODS;
    return list;
}
