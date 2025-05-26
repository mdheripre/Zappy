/*
** EPITECH PROJECT, 2025
** server
** File description:
** handle_poll
*/


#include "server.h"
#include "utils.h"

static void read_from_client(server_t *self, int index)
{
    client_t *client = &self->clients[index];
    char buf[128];
    ssize_t bytes = read(client->fd, buf, sizeof(buf));

    if (bytes <= 0) {
        console_log(LOG_INFO, "Client (fd=%d) disconnected", client->fd);
        remove_client(self, index);
        return;
    }
    if (client->buffer_len + bytes < CLIENT_BUFFER_SIZE) {
        memcpy(client->read_buffer + client->buffer_len, buf, bytes);
        client->buffer_len += bytes;
        client->read_buffer[client->buffer_len] = '\0';
        console_log(LOG_INFO, "Client %d buffer: \"%s\"",
            client->fd, client->read_buffer);
    } else {
        console_log(LOG_WARNING, "Buffer overflow for client %d",
            client->fd);
        remove_client(self, index);
    }
}

void handle_server_poll(server_t *self, struct pollfd *fds)
{
    int client_index = 0;

    if (fds[0].revents & POLLIN)
        self->vtable->accept_client(self);
    for (int i = 1; i <= self->client_count; i++) {
        if (fds[i].revents & (POLLIN | POLLHUP)) {
            read_from_client(self, client_index);
            continue;
        }
        client_index++;
    }
}
