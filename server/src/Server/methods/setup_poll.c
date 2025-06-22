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
 * @brief Sets up the poll structure for the server and its clients.
 *
 * This function initializes the poll file descriptors for the server's
 * socket and all connected clients. It prepares the poll structure to
 * monitor events on these file descriptors.
 *
 * @param self Pointer to the server instance.
 * @param fds Pointer to an array of pollfd structures to be filled.
 * @param nfds Pointer to the number of file descriptors in the fds array.
 */
void setup_server_poll(server_t *self, struct pollfd *fds, nfds_t *nfds)
{
    list_node_t *node = NULL;
    client_t *client = NULL;

    *nfds = 1;
    fds[0].fd = self->socket_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    for (node = self->clients->head; node; (*nfds)++) {
        client = node->data;
        if (!client)
            continue;
        fds[*nfds].fd = client->fd;
        fds[*nfds].events = POLLIN;
        fds[*nfds].revents = 0;
        node = node->next;
    }
}
