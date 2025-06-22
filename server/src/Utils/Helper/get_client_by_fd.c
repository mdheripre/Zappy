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
    list_node_t *node = NULL;
    client_t *client = NULL;

    if (!server || !server->clients)
        return NULL;
    for (node = server->clients->head; node; node = node->next) {
        client = node->data;
        if (client && client->fd == fd)
            return client;
    }
    return NULL;
}
