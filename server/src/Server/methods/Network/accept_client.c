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

static int accept_fd(server_t *self)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    return accept(self->socket_fd, (struct sockaddr *)&client_addr, &addr_len);
}

static bool is_server_full(server_t *self)
{
    if (self->client_count >= MAX_CLIENTS) {
        console_log(LOG_WARNING, "Too many clients. Connection refused.");
        return true;
    }
    return false;
}

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
    client->connected = true;
    self->client_count++;
    EMIT(self->dispatcher, "client_connected", client);
}
