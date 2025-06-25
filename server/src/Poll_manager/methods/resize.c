/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** resize
*/

#include "poll_manager.h"

/****************************************************************************/
/*                                                                          */
/*                               METHODS                                    */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Resizes the pollfd array in the poll manager to a new capacity.
 *
 * Allocates a new array of pollfd structures with the specified size,
 * copies existing entries, updates the manager, and handles memory
 * registration.
 *
 * @param mgr Pointer to the poll manager structure.
 * @param new_size The desired new capacity for the pollfd array.
 * @return true on success, false on allocation failure.
 */
bool poll_manager_resize(poll_manager_t *mgr, size_t new_size)
{
    struct pollfd *new_fds = NULL;

    if (!mgr || mgr->capacity >= new_size)
        return true;
    new_fds = calloc(new_size, sizeof(struct pollfd));
    if (!new_fds)
        return false;
    memcpy(new_fds, mgr->fds, mgr->nfds * sizeof(struct pollfd));
    gc_unregister(mgr->fds);
    free(mgr->fds);
    gc_register(new_fds, NULL);
    mgr->fds = new_fds;
    mgr->capacity = new_size;
    return true;
}
