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

#include <fcntl.h>

/****************************************************************************/
/*                                                                          */
/*                             CLIENT MANAGEMENT                            */
/*                                                                          */
/****************************************************************************/


/**
 * @brief Sets the given file descriptor to non-blocking mode.
 *
 * @param fd The file descriptor to modify.
 */
static void set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1)
        return;
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/**
 * @brief Accepts a new client connection on the server socket.
 *
 * This function accepts an incoming connection, sets the new socket
 * to non-blocking mode, and returns its file descriptor.
 *
 * @param self Pointer to the server structure.
 * @return File descriptor of the accepted client, or -1 on error.
 */
static int accept_fd(server_t *self)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int fd = accept(self->socket_fd, (struct sockaddr *)&client_addr,
        &addr_len);

    if (fd >= 0)
        set_nonblocking(fd);
    return fd;
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
    if (self->client_count >= self->game->max_players) {
        console_log(LOG_WARNING, "Too many clients. Connection refused.");
        return true;
    }
    return false;
}

/**
 * @brief Initializes a new client structure for the server.
 *
 * Allocates and sets up a client_t instance in the server's client array,
 * initializes its fields, and creates a command list for the client.
 *
 * @param self Pointer to the server structure.
 * @param fd File descriptor for the new client connection.
 * @return Pointer to the initialized client_t, or NULL on failure.
 */
static client_t *init_client(server_t *self, int fd)
{
    client_t *client = calloc(1, sizeof(client_t));

    if (!client)
        return NULL;
    client->fd = fd;
    client->type = CLIENT_UNDEFINED;
    client->connected = true;
    client->stuck = false;
    client->commands = NEW(list, free);
    if (!client->commands) {
        console_log(LOG_ERROR, "Failed to create command list for client.");
        close(fd);
        free(client);
        return NULL;
    }
    self->clients->methods->push_back(self->clients, client);
    return client;
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
    client = init_client(self, client_fd);
    if (!client)
        return;
    self->client_count++;
    EMIT(self->dispatcher, "client_connected", client);
}
