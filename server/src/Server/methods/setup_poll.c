/*
** EPITECH PROJECT, 2025
** server
** File description:
** setup_poll
*/

#include "server.h"
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                                POLLING SYSTEM                            */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Adds the server socket to the pollfd array.
 *
 * Sets up the poll structure to monitor the server's listening socket.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structures.
 * @param nfds Pointer to the number of file descriptors used.
 */
static void setup_server_socket_poll(server_t *self, struct pollfd *fds,
    nfds_t *nfds)
{
    *nfds = 0;
    fds[*nfds] = (struct pollfd){
        .fd = self->socket_fd,
        .events = POLLIN,
        .revents = 0,
    };
    (*nfds)++;
}

/**
 * @brief Adds all connected clients to the pollfd array.
 *
 * Iterates over connected clients and sets their socket for polling.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structures.
 * @param nfds Pointer to the number of file descriptors used.
 */
static void setup_clients_poll(server_t *self, struct pollfd *fds,
    nfds_t *nfds)
{
    list_node_t *node = self->clients->head;
    client_t *client = NULL;

    for (; node; node = node->next) {
        client = node->data;
        if (!client)
            continue;
        fds[*nfds] = (struct pollfd){
            .fd = client->fd,
            .events = POLLIN,
            .revents = 0,
        };
        (*nfds)++;
    }
}

/**
 * @brief Sets up polling for both server socket and all clients.
 *
 * Combines server socket and clients into a single pollfd array.
 *
 * @param self Pointer to the server instance.
 * @param fds Array of pollfd structures.
 * @param nfds Pointer to the number of file descriptors used.
 */
void setup_server_poll(server_t *self, struct pollfd *fds,
    nfds_t *nfds)
{
    setup_server_socket_poll(self, fds, nfds);
    setup_clients_poll(self, fds, nfds);
}
