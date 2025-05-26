/*
** EPITECH PROJECT, 2025
** server
** File description:
** setup_poll
*/

#include "server.h"
#include "utils.h"

void setup_server_poll(server_t *self, struct pollfd *fds, nfds_t *nfds)
{
    *nfds = 1;
    fds[0].fd = self->socket_fd;
    fds[0].events = POLLIN;
    for (int i = 0; i < self->client_count; i++) {
        fds[*nfds].fd = self->clients[i].fd;
        fds[*nfds].events = POLLIN;
        (*nfds)++;
    }
}
