/*
** EPITECH PROJECT, 2025
** server
** File description:
** destroy_server
*/

#include "server.h"

/****************************************************************************/
/*                                                                          */
/*                            DESTRUCTOR                                    */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Destroys the server instance and cleans up resources.
 *
 * Closes the server socket and resets the socket file descriptor.
 *
 * @param self Pointer to the server instance to destroy.
 */
void server_destroy(server_t *self)
{
    if (!self)
        return;
    if (self->socket_fd != -1)
        close(self->socket_fd);
    self->socket_fd = -1;
}
