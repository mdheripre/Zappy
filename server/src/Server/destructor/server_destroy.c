/*
** EPITECH PROJECT, 2025
** server
** File description:
** destroy_server
*/

#include "server.h"

void server_destroy(server_t *self)
{
    if (!self)
        return;
    if (self->socket_fd != -1)
        close(self->socket_fd);
    self->socket_fd = -1;
}
