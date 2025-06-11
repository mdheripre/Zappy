/*
** EPITECH PROJECT, 2025
** server
** File description:
** get_client_by_fd
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER SERVER                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Returns a pointer to the client with the given file descriptor.
 *
 * @param server Pointer to the server instance.
 * @param fd File descriptor to search.
 * @return client_t* Pointer to the matching client, or NULL if not found.
 */
client_t *get_client_by_fd(server_t *server, int fd)
{
    if (!server)
        return NULL;
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].fd == fd)
            return &server->clients[i];
    }
    return NULL;
}
