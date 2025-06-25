/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** get_fds
*/

#include "poll_manager.h"

/****************************************************************************/
/*                                                                          */
/*                               METHODS                                    */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Retrieves the array of pollfd structures managed by the poll manager.
 *
 * @param mgr Pointer to the poll manager instance.
 * @param out_nfds Output pointer to store the number of file descriptors.
 * @return Pointer to the array of pollfd structures, or NULL on error.
 */
struct pollfd *poll_manager_get_fds(poll_manager_t *mgr, nfds_t *out_nfds)
{
    if (!mgr || !out_nfds)
        return NULL;
    *out_nfds = mgr->nfds;
    return mgr->fds;
}
