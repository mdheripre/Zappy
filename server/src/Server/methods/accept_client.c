/*
** EPITECH PROJECT, 2025
** server
** File description:
** accept_client
*/

#include "server.h"
#include "utils.h"
#include "dispatcher.h"
#include "shared.h"


/****************************************************************************/
/*                                                                          */
/*                             CLIENT MANAGEMENT                            */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Accepts a new client connection.
 *
 * This function accepts a new client connection on the server's socket.
 * It retrieves the client's address and returns the file descriptor for
 * the accepted socket.
 *
 * @param self Pointer to the server instance.
 * @return The file descriptor for the accepted client socket, or -1 on error.
 */
static int accept_fd(server_t *self)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    return accept(self->socket_fd, (struct sockaddr *)&client_addr, &addr_len);
}

/**
 * @brief Checks if the server has reached its maximum client limit.
 *
 * This function checks if the current number of connected clients
 * exceeds the maximum allowed clients. If it does, it logs a warning
 * and returns true, indicating that no more clients can be accepted.
 *
 * @param self Pointer to the server instance.
 * @return true if the server is full, false otherwise.
 */
static bool is_server_full(server_t *self)
{
    if (self->client_count >= MAX_CLIENTS) {
        console_log(LOG_WARNING, "Too many clients. Connection refused.");
        return true;
    }
    return false;
}

/**
 * @brief Accepts a new client connection and initializes the client structure.
 *
 * This function accepts a new client connection, checks if the server is full,
 * and initializes the client structure with the client's file descriptor and
 * default values. It then emits a "client_connected" event to notify the
 * system of the new client connection.
 *
 * @param self Pointer to the server instance.
 */
void accept_client(server_t *self)
{
    int client_fd = accept_fd(self);
    client_t *client = NULL;

    if (client_fd == -1) {
        console_log(LOG_WARNING, "Failed to accept client: %s",
            strerror(errno));
        return;
    }
    if (is_server_full(self)) {
        close(client_fd);
        return;
    }
    client = &self->clients[self->client_count];
    client->fd = client_fd;
    client->type = CLIENT_UNDEFINED;
    client->connected = true;
    client->stuck = false;
    self->client_count++;
    EMIT(self->dispatcher, "client_connected", client);
}
