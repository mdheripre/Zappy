/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** poll_manager_create
*/

#include "poll_manager.h"


poll_manager_t *poll_manager_create(size_t initial_size)
{
    poll_manager_t *mgr = calloc(1, sizeof(poll_manager_t));

    if (!mgr)
        return NULL;
    mgr->fds = calloc(initial_size, sizeof(struct pollfd));
    if (!mgr->fds) {
        free(mgr);
        return NULL;
    }
    gc_register(mgr->fds, NULL);
    mgr->capacity = initial_size;
    mgr->nfds = initial_size;
    mgr->methods.resize = poll_manager_resize;
    mgr->methods.get_fds = poll_manager_get_fds;
    mgr->methods.destroy = poll_manager_destroy;
    return mgr;
}
