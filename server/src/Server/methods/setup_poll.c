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

void setup_server_poll(server_t *self, struct pollfd *fds,
    nfds_t *nfds)
{
    setup_server_socket_poll(self, fds, nfds);
    setup_clients_poll(self, fds, nfds);
}
