/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** get_fds
*/

#include "poll_manager.h"

struct pollfd *poll_manager_get_fds(poll_manager_t *mgr, nfds_t *out_nfds)
{
    if (!mgr || !out_nfds)
        return NULL;
    *out_nfds = mgr->nfds;
    return mgr->fds;
}
